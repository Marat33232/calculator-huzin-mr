import subprocess

def test_integer_mode():
    result = subprocess.run(["../build/app.exe"], input="5 + 3\n", text=True, capture_output=True)
    assert result.returncode == 0
    assert result.stdout.strip() == "8"

def test_float_mode():
    result = subprocess.run(["../build/app.exe", "--float"], input="5 / 3\n", text=True, capture_output=True)
    assert result.returncode == 0
    assert abs(float(result.stdout.strip()) - 1.6667) < 1e-4

def test_invalid_input():
    result = subprocess.run(["../build/app.exe"], input="5 + a\n", text=True, capture_output=True)
    assert result.returncode != 0

def test_division_by_zero():
    result = subprocess.run(["../build/app.exe"], input="5 / 0\n", text=True, capture_output=True)
    assert result.returncode != 0
