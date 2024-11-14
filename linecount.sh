echo "Lines of code in project:"

echo "Headers:"
wc -l $(find src -type f -name "*.h")

echo "Code:"
wc -l $(find src -type f -name "*.c")

echo "Total:"
wc -l $(find src -type f -name "*.c") $(find src -type f -name "*.h")