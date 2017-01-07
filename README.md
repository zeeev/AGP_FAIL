# AGP_FAIL

This code checks that gaps in an AGP file lineup with the scaffolds in a fasta.  If they don't you've got trouble.  

Hateful bug reports are very welcome!


# installing
```
git clone --recursive https://github.com/zeeev/AGP_FAIL.git
cd AGP_FAIL && make
```
# running


```
Usage: agp-fail <AGP.txt> <fasta.fa>

Required: AGP   <STRING> - An AGP v2.0 file.
          FASTA <STRING> - The fasta that matches the AGP.

Details:  This program checks your fasta against your AGP and INSULTS you!
```
