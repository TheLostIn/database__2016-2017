# !bin/bash
rm `find . \( -name "*.dsp" -o -name "*.dep" -o -name "*.dsw" -o -name "*.mak" -o -name "*.ncb" -o -name "*.plg" -o -name "*.opt" \)`
rm -r `find . -type d -name "Debug"`
