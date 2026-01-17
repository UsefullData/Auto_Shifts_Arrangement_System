# app.py
from flask import Flask, render_template, request
import subprocess
import json
import os

app = Flask(__name__)

# Path to your compiled C++ executable
# IF ON WINDOWS, USE 'core\\prog.exe'
# IF ON MAC/LINUX, USE './core/prog'
EXECUTABLE_PATH = os.path.join('core', 'prog.exe') 

@app.route('/', methods=['GET', 'POST'])
def index():
    data = None
    
    if request.method == 'POST':
        # 1. Get data from HTML form
        staff_count = request.form.get('staff_count')
        day_count = request.form.get('day_count')
        min_off = request.form.get('min_off')
        rate = request.form.get('rate')

        # 2. Run the C++ program silently
        try:
            result = subprocess.run(
                [EXECUTABLE_PATH, staff_count, day_count, min_off, rate],
                capture_output=True,
                text=True,
                check=True
            )
            
            # 3. Extract the JSON part from C++ output
            output = result.stdout
            start_marker = "---JSON_START---"
            end_marker = "---JSON_END---"
            
            if start_marker in output and end_marker in output:
                json_str = output.split(start_marker)[1].split(end_marker)[0]
                data = json.loads(json_str)
            else:
                print("Error: Could not find JSON in C++ output")
                print(output) # Debugging

        except Exception as e:
            print(f"Error running C++: {e}")

    return render_template('index.html', data=data)

if __name__ == '__main__':
    app.run(debug=True)