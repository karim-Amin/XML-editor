# XML-Parser
Best xml editor from scratch

## Abstract
 XML format was the first used to transfer data via the internet during its early day. Though, it's still cruical to master these concepts which explains how the web really works. Now, its predesessor JSON used extensively and enabled the new efficient RESTful APIs which expanded web services in the way we know today.
In this project we aim to understand the different formats used in the web by making our own application manipulating these different kinds of data.

## Goals
 To build a GUI application able to: 
 - Correct xml files.
 - Format and Identation.
 - Convert xml files into JSON.
 - Reducing file size by removing extra spaces.
 - compress the file to reduce its size.

## Background
XML files is common format to transfer data across the internet gained its popularity in the early days of the web due to the vast similarity with HTML syntax. Now, a better alternative is JSON format which stands for JavaScript Object Notation. both of these formats are used to send data in HTTP requests.
Due to the similarity with HTML we will adopt the DOM - Document Object Model - model used in modern browsers by parsing the file as a tree and applying different operations as needed by the user.

## Implementation Details

### GUI

### Fixing Errors

### Formatting
 Good formatting needs good understanding of the data. The file is Parse into a tree where each node is called a tag.
 Each tag has a name, map - key-value pairs - of attributes, list of childten, parent ,and the included text.
 The number of children of each tag is not limited.
 three pointers are used to keep track and construct the tree:
 - pointer to the root
 - pointer to the head -the current tag to inset in its children-
 - pointer to the parent to be able to traverse the tree as each tag is allowed to have multiple children

To format the text a depth variable is used which is guided by the depth of the tree. As you traverse the tree the depth variable increases or decreases providig a good metric for identation.
extra spaces and symbols are added and printed as needed.

 ![file before formatting](https://github.com/KareimGazer/XML-Parser/blob/main/screenshots/rawData.PNG?raw=true)
 
 file before formatting.
 
  ![file after formatting](https://github.com/KareimGazer/XML-Parser/blob/main/screenshots/formatted.PNG?raw=true)
  
  file after formatting.

### Converting XML to JSON

By using the same parse tree but instead of using xml characters and notation, JSON notation was used according to standards.

 ![file after JSON formatting](https://github.com/KareimGazer/XML-Parser/blob/main/screenshots/json.PNG?raw=true)

### Minifying XML file
extra spaces were removed by removing "\n" while reading the file and using regex to remove more than one space.

 ![file after JSON formatting](https://github.com/KareimGazer/XML-Parser/blob/main/screenshots/mini.PNG?raw=true)

### Data Compression
 Huffman codes is a greedy algorithms which relys on "make the common case smaller" principle. In short, it compresses the data by preserving shorter bit streams for the more frequent letter and words. This means that the file to be constructed need to be studied for characters frequency. We used a simple script to count the number of occurences of each character in the file and store the result in a map then we sort them by value. This is done for every file before being processed instead of relying on generalization of characters frequency which degrades the alorithm performance of the alorithms in practical cases.
 
 A tree in which the most frequent characters are near the root is constructed greedly starting from the less to the more frequent characters. code is generated by traversing the tree, left generates a zero and right generates a one.
 after code generation the data is written in a binary file.
 Data is retrevied by traversing the tree using the codes until reaching the characters.
 
 The Algorithm generated half the size on average.
 
 ![files size](https://github.com/KareimGazer/XML-Parser/blob/main/screenshots/compression.PNG?raw=true)
 
### Complexity of Operations
In all three of formatting, converting, compression the primary Data Structures was the tree whether it's parse tree or huffman code tree of characters providing   O(logN) operations for accessing tags and characters nodes. where N is the number of tree nodes.
for formatting the operations was O(N) where N is the number of lines in the file as each line was scanned and cleared from extra white spaces.

### Testing
For testing, in addition to the sample files provided in the report extra files with diffrent format from the web were collected.
All files can be found in Test folder

## Sources
- converting from XML to JSON https://www.xml.com/pub/a/2006/05/31/converting-between-xml-and-json.html?fbclid=IwAR1Y5xWga_pcYSSR3SwCDyXKDpnKZp1ZG0otr53ZT8sk0eypqSzH5b_36kQ
- Huffman code Compression Algorithms https://www.coursera.org/learn/algorithms-greedy
- Programming tips and tricks https://geeksforgeeks.org and https://stackoverflow.com/

