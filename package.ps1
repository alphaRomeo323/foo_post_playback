$ErrorActionPreference = "silentlycontinue"

$targetDir= $Args[0]
if (-not ($targetDir)) { return 100 } 
$componentName= $Args[1]
if (-not ($componentName)) { return 101 }

$targetPath= $targetDir + $componentName + ".dll"
$tempFilePath = $targetDir + $componentName + ".zip"
$outFilePath = $targetDir + $componentName + ".fb2k-component"

Remove-Item $tempFilePath
Remove-Item $outFilePath

Get-ChildItem -Path $targetPath | Compress-Archive -DestinationPath $tempFilePath

Move-Item $tempFilePath $outFilePath


