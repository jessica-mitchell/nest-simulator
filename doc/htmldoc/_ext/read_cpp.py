
# This extension should find the cpp info
import os
import re
import json



def process_files(directory):
    result = {}
    pattern = r'\/\*\*\s*DocKeywords:\s*(.*?)\s*\*\/(?:\s*\w+\s*)+class\s+(\w+)\b'
    regex = re.compile(pattern, re.DOTALL)
    
    for filename in os.listdir(directory):
        if filename.endswith(".h") or filename.endswith(".hpp"):
            file_path = os.path.join(directory, filename)
            with open(file_path, 'r') as file:
                content = file.read()
                matches = regex.findall(content)
                for match in matches:
                    keywords = match[0].split(',')
                    class_name = match[1]
                    result[class_name] = [keyword.strip() for keyword in keywords]
    
    return result

# Example usage
# Example usage
directory_path = "../../nestkernel/"
output_file_path = "cpp-class-keyword.json"

result_dict = process_files(directory_path)

with open(output_file_path, 'w') as output_file:
    json.dump(result_dict, output_file)

