# main.py

import importlib
import os
import sys
import subprocess
from mqtt_framework.logger import setup_logger

sys.path.append(os.path.abspath(os.path.dirname(__file__)))

logger = setup_logger("main_handler")

def load_and_run_modules(directory):
    processes = []
    for filename in os.listdir(directory):
        if filename.endswith(".py") and filename != "__init__.py":
            module_name = filename[:-3]  # Remove the .py extension
            try:
                logger.info(f"Starting {module_name}...")
                
                env = os.environ.copy()
                env["PYTHONPATH"] = os.path.abspath(os.path.dirname(__file__)) 
                
                # Check if it's a Publisher or Subscriber
                if 'publisher' in directory:
                    # Start Publisher in a separate process
                    process = subprocess.Popen(['python3', f'publishers/{module_name}.py'], env=env)
                    processes.append(process)
                elif 'subscriber' in directory:
                    # Start Subscriber in a separate process
                    process = subprocess.Popen(['python3', f'subscribers/{module_name}.py'], env=env)
                    processes.append(process)
            except Exception as e:
                logger.error(f"Failed to load {module_name}: {e}")

    return processes

if __name__ == "__main__":
    logger.info("Starting system...")
    
    # Load and run all modules from publishers and subscribers
    processes = load_and_run_modules("publishers")
    processes += load_and_run_modules("subscribers")

    # Wait for all processes to finish (keep the main process alive)
    for process in processes:
        process.wait()  # Wait for each process to finish
    logger.info("All processes have completed.")
