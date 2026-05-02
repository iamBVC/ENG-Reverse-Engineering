ffmpeg.exe -i "%~1" -c:v libx264 -pix_fmt yuv420p -crf 18 -preset medium -c:a aac -b:a 160k -movflags +faststart output.mp4
  pause