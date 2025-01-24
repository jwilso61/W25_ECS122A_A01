# Path to the main test directory
$testDir = ".\test_data"

# Path to the program
$program = ".\a.exe"

# Loop through each numbered directory
Get-ChildItem -Path $testDir -Directory | ForEach-Object {
    $testCaseDir = $_.FullName

    # Get the input and expected output file paths
    $inputFile = Join-Path $testCaseDir "input"
    $expectedOutputFile = Join-Path $testCaseDir "output"
    $actualOutputFile = Join-Path $testCaseDir "actual_output.txt"

    # Run the program and save the output
    Get-Content $inputFile | & $program > $actualOutputFile

    # Compare the actual output with the expected output
    if (Compare-Object (Get-Content $expectedOutputFile) (Get-Content $actualOutputFile) -SyncWindow 0) {
        Write-Host "Test case in ${testCaseDir}: FAILED" -ForegroundColor Red
    } else {
        Write-Host "Test case in ${testCaseDir}: PASSED" -ForegroundColor Green
    }
}

#To Run: change to CA# directory and run C:\Users\jwils\OneDrive\Desktop\Academics\W25\ECS122A\W25_ECS122A_A01\W25_ECS122A_A01\test_runner.ps1