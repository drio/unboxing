#!/usr/bin/env python3
import os
import glob
import re
from collections import defaultdict

def find_palette_images():
    """Find all palette images and group by palette number"""
    images = defaultdict(list)
    pattern = re.compile(r'palette_(\d+)_.*\.png')
    
    for filename in glob.glob('palette_*.png'):
        match = pattern.match(filename)
        if match:
            palette_num = int(match.group(1))
            images[palette_num].append(filename)
    
    # Sort images within each palette
    for palette_num in images:
        images[palette_num].sort()
    
    return images

def generate_html(images):
    """Generate the HTML content"""
    html = '''<!DOCTYPE html>
<html>

<head>
    <title>Fractal Gallery</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            margin: 0px;
            background: black;
        }

        .gallery {
            display: grid;
            grid-template-columns: repeat(auto-fit, minmax(250px, 1fr));
            gap: 5px;
        }

        .fractal {
            background: black;
            border-radius: 0px;
            padding: 5px;
            box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1);
        }

        img {
            width: 100%;
            height: auto;
            border-radius: 4px;
            display: block;
        }
    </style>
</head>

<body>
    <div class="gallery">
'''
    
    # Generate images in palette order
    for palette_num in sorted(images.keys()):
        for image_file in images[palette_num]:
            html += f'''        <div class="fractal">
            <a href="{image_file}" target="_blank">
                <img src="{image_file}" alt="Palette {palette_num}">
            </a>
        </div>

'''
    
    html += '''    </div>
</body>

</html>
'''
    return html

def main():
    images = find_palette_images()
    
    if not images:
        print("No palette images found. Generate some first with: make")
        return
    
    html_content = generate_html(images)
    
    with open('index.html', 'w') as f:
        f.write(html_content)
    
    total_images = sum(len(files) for files in images.values())
    print(f"Generated index.html with {total_images} images across {len(images)} palettes")

if __name__ == '__main__':
    main()