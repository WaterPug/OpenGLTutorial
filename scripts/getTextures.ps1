$url1 = "https://learnopengl.com/img/textures/container.jpg"
$url2 = "https://learnopengl.com/img/textures/awesomeface.png"

Invoke-WebRequest $url1 -OutFile ..\data\container.jpg
Invoke-WebRequest $url2 -OutFile ..\data\face.png