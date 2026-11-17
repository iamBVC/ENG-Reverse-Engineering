param(
    [Parameter(Mandatory = $true)]
    [string]$ExportDirectory,
    [string[]]$RequiredAddresses = @("00447770", "004CB870")
)

$indexPath = Join-Path $ExportDirectory "_index.csv"
if (-not (Test-Path -LiteralPath $indexPath)) {
    throw "Missing export index: $indexPath"
}

$rows = @(Import-Csv -LiteralPath $indexPath)
if ($rows.Count -eq 0) {
    throw "Export index contains no functions: $indexPath"
}

$duplicateNames = @($rows | Group-Object name | Where-Object { $_.Count -gt 1 })
if ($duplicateNames.Count -gt 0) {
    throw "Duplicate function names: $($duplicateNames.Name -join ', ')"
}

if ($rows[0].PSObject.Properties.Name -notcontains "file") {
    throw "Export index has no filename column; exports cannot be checked for collisions"
}

$duplicateFiles = @($rows | Group-Object file | Where-Object { $_.Count -gt 1 })
if ($duplicateFiles.Count -gt 0) {
    throw "Duplicate export filenames: $($duplicateFiles.Name -join ', ')"
}
$duplicateAddresses = @($rows | Group-Object address | Where-Object { $_.Count -gt 1 })
if ($duplicateAddresses.Count -gt 0) {
    throw "Duplicate function addresses: $($duplicateAddresses.Name -join ', ')"
}

$expectedThunks = @(
    @{ Address = "0043CB20"; Target = "sub_545270" },
    @{ Address = "0043CB30"; Target = "sub_545030" }
)
foreach ($expected in $expectedThunks) {
    $thunk = $rows | Where-Object { $_.address.ToUpperInvariant() -eq $expected.Address } | Select-Object -First 1
    if ($null -eq $thunk -or $thunk.status -ne "ok") {
        throw "Missing successful thunk export at $($expected.Address)"
    }
    if ([string]::IsNullOrWhiteSpace($thunk.name) -or $thunk.name -eq $expected.Target) {
        throw "Thunk $($expected.Address) does not have a distinct exported name"
    }
    $thunkPath = Join-Path $ExportDirectory $thunk.file
    $thunkSource = Get-Content -LiteralPath $thunkPath -Raw
    if ($thunkSource -notmatch "\b$($thunk.name)\s*\([^)]*\)\s*\{[^}]*\b$($expected.Target)\s*\(\s*\)\s*;" -or
        $thunkSource -match "\b$($thunk.name)\s*\(\s*\)\s*;") {
        throw "Thunk $($expected.Address) does not forward to $($expected.Target)"
    }
}

$missingFiles = @($rows | Where-Object {
    $_.status -eq "ok" -and -not (Test-Path -LiteralPath (Join-Path $ExportDirectory $_.file))
})
if ($missingFiles.Count -gt 0) {
    throw "Successful functions are missing output files: $($missingFiles.address -join ', ')"
}

$misidentifiedFiles = @($rows | Where-Object {
    if ($_.status -ne "ok") { return $false }
    $path = Join-Path $ExportDirectory $_.file
    $header = Get-Content -LiteralPath $path -TotalCount 1
    return $header -notlike "/* $($_.name) @ $($_.address)*"
})
if ($misidentifiedFiles.Count -gt 0) {
    throw "Output file headers do not match indexed functions: $($misidentifiedFiles.address -join ', ')"
}

$requiredFailures = @($RequiredAddresses | Where-Object {
    $requiredAddress = $_.ToUpperInvariant()
    $match = $rows | Where-Object { $_.address.ToUpperInvariant() -eq $requiredAddress } | Select-Object -First 1
    $null -eq $match -or $match.status -ne "ok"
})
if ($requiredFailures.Count -gt 0) {
    throw "Required functions are missing or failed: $($requiredFailures -join ', ')"
}

$requiredMessage = if ($RequiredAddresses.Count -gt 0) {
    "required functions present ($($RequiredAddresses -join ', '))"
} else {
    "no additional required addresses"
}
"PASS: $($rows.Count) indexed functions, unique addresses and filenames, matching files present, $requiredMessage."
