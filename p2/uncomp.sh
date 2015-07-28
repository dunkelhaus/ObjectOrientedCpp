#!/bin/bash
#umcompressing files
#.gz, .tar,.tar.gz,.zip,.tg
if [[ $# -eq 0 ]]; then
echo "usage: uncomp {filelist}+"
exit
fi

for file in $@; do
   case $file in
    *.tar.gz)
    tar -xzf $file;;
    
   *.tgz)
   tar -xzf $file;;
   *.gz) 
   gunzip $file;;  
 
  *.tar) 
     tar -xf $file;;
  *.zip) 

     unzip -q $file ;;  
 *)
   echo "uncomp: $file has no compression extension.";;
esac
done   

