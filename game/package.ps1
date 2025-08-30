$buildDir = "../build"
$sdl3Dir = "C:/DEV/SDL3/x64"
$sdl3_imageDir = "C:/DEV/SDL3_image/x64"
$mingwDir = "C:/mingw64/bin"

# Copiar DLLs
Copy-Item "$sdl3Dir/bin/SDL3.dll" -Destination $buildDir
Copy-Item "$sdl3_imageDir/bin/SDL3_image.dll" -Destination $buildDir
Copy-Item "$mingwDir/libwinpthread-1.dll" -Destination $buildDir
Copy-Item "$mingwDir/libgcc_s_seh-1.dll" -Destination $buildDir
Copy-Item "$mingwDir/bin/libstdc++-6.dll" -Destination $buildDir

# Copiar assets
Copy-Item "../assets" -Destination $buildDir -Recurse
Copy-Item "options.txt" -Destination $buildDir

Write-Host "¡Paquete creado en la carpeta $buildDir!"