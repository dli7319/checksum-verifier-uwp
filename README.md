# Checksum Generator & Validator Universal Windows App
Written in C++    
Uses openssl for all checksum calculations    
Inspired by https://raylin.wordpress.com/downloads/md5-sha-1-checksum-utility/

Screenshots
--------------------------------
![Screenshot1](Readme_Assets/Screenshot1.png?raw=true)

TODO (For Robel)
--------------------------------
* Add actions to click/unclick checkboxes and copy/paste
  * Due March 1
* Fix memory leaks. (Stop reading the whole file into memory)
  * Due March 15
* Multithreaded computation (stop blocking main thread)
  * Due March 22
* Tabbed UI with About Page and Link to Robel's Website
  * Due March 29
* Folder support
* Write to file (MD5SUMS, SHA1SUMS)
* Read from file (MD5SUMS, SHA1SUMS)
* Cloud support - Check with known hashes on a database to automatically verify common files
* GPG Checks
* Update Screenshots with all the above
