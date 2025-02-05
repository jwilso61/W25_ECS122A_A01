# # Path to the main test directory
# $testDir = ".\test_data"

# # Path to the program
# $program = ".\a.exe"

# # Loop through each numbered directory
# Get-ChildItem -Path $testDir -Directory | ForEach-Object {
#     $testCaseDir = $_.FullName

#     # Get the input and expected output file paths
#     $inputFile = Join-Path $testCaseDir "input"
#     $expectedOutputFile = Join-Path $testCaseDir "output"
#     $actualOutputFile = Join-Path $testCaseDir "actual_output.txt"

#     # Run the program and save the output
#     Get-Content $inputFile | & $program > $actualOutputFile

#     # Compare the actual output with the expected output
#     if (Compare-Object (Get-Content $expectedOutputFile) (Get-Content $actualOutputFile) -SyncWindow 0) {
#         Write-Host "Test case in ${testCaseDir}: FAILED" -ForegroundColor Red
#     } else {
#         Write-Host "Test case in ${testCaseDir}: PASSED" -ForegroundColor Green
#     }
# }

#To Run: change to CA# directory and run "C:\Users\jwils\OneDrive\Desktop\Academics\W25\ECS122A_A01\test_runner.ps1"
# otherwise use  Get-Content .\test_data\01\input | .\a.exe > .\test_data\01\actual_output.txt



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

    # Ensure input and output files exist
    if (-Not (Test-Path $inputFile) -or -Not (Test-Path $expectedOutputFile)) {
        Write-Host "Missing input or expected output file in ${testCaseDir}. Skipping..." -ForegroundColor Yellow
        return
    }

    # Run the program and save the output
    Get-Content $inputFile | & $program > $actualOutputFile

    # Ensure the program produced an output file
    if (-Not (Test-Path $actualOutputFile) -or (Get-Content $actualOutputFile).Length -eq 0) {
        Write-Host "No output produced by the program for test case in ${testCaseDir}. Skipping..." -ForegroundColor Yellow
        return
    }

    # Compare the actual output with the expected output
    if (Compare-Object (Get-Content $expectedOutputFile) (Get-Content $actualOutputFile) -SyncWindow 0) {
        Write-Host "Test case in ${testCaseDir}: FAILED" -ForegroundColor Red
    } else {
        Write-Host "Test case in ${testCaseDir}: PASSED" -ForegroundColor Green
    }
}
