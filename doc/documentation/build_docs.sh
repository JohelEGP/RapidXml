echo Step 1: Running doxygen on RapidXml sources...
doxygen

echo Step 2: Running xltproc on doxygen output...
cd xml
cp ../reference.xsl reference.xsl
xsltproc -o ../tmp.html reference.xsl index.xml
rm -f reference.xsl
cd ..

echo Step 3: Running postprocessor on xltproc output...
bin/postprocessor < tmp.html > ../../manual.html
rm tmp.html

echo Done.
