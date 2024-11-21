#!/bin/bash

set -e

# Function to check and install a package
check_and_install() {
    if ! command -v "$1" &> /dev/null; then
        echo "$1 is not installed. Installing $1..."
        sudo apt-get update
        sudo apt-get install -y "$2"
    else
        echo "$1 is already installed."
    fi
}

# Function to download and install a font
download_and_install_font() {
    local font_name="$1"
    local font_url="$2"
    local font_filename="$3"

    if ! fc-list | grep -i "$font_name" &> /dev/null; then
        echo "$font_name font is not installed. Downloading and installing $font_name..."
        wget "$font_url" -O "$font_filename" -q --show-progress
        sudo mkdir -p /usr/local/share/fonts/
        sudo mv "$font_filename" /usr/local/share/fonts/

        sudo unzip -j /usr/local/share/fonts/"$font_filename" '*.ttf' -d /usr/local/share/fonts/

        sudo rm /usr/local/share/fonts/"$font_filename"

        fc-cache -f -v
    else
        echo "$font_name font is already installed."
    fi
}

# Check and install required packages
check_and_install "pandoc" "pandoc"
check_and_install "pdflatex" "texlive-full"
check_and_install "wget" "wget"

# Download and install required fonts
download_and_install_font "IBM Plex Sans KR" "https://github.com/IBM/plex/releases/download/v6.0.0/TrueType.zip" "IBMPlex.zip"

download_and_install_font "D2Coding" "https://github.com/naver/d2codingfont/releases/download/VER1.3.2/D2Coding-Ver1.3.2-20180524.zip" "D2Coding.zip"

# Output PDF filename
output_file="output.pdf"

# Find all markdown files in the current directory and subdirectories, sort them by modification time
markdown_files=$(find . -name "*.md" -type f -printf '%T@ %p\n' | sort -n | cut -d' ' -f2-)

# Check if index.md exists and put it at the beginning of the list
if [[ -f "index.md" ]]; then
    markdown_files=$(echo -e "index.md\n$(echo "$markdown_files" | grep -v "index.md")")
fi

echo "Converting the following Markdown files to PDF:"
echo "$markdown_files"

# Compile the markdown files into a single PDF using pandoc with Unicode support
pandoc $markdown_files \
    --pdf-engine=xelatex \
    -V mainfont="IBM Plex Sans KR" \
    -V monofont="D2Coding" \
    -V monofontfallback="IBM Plex Sans KR" \
    -V fontsize=11pt \
    -V geometry:margin=1in \
    --toc \
    --highlight-style=tango \
    -o "$output_file"

echo "Compilation complete. Output saved as $output_file"