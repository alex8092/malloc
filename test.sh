
setenv DYLD_LIBRARY_PATH .
setenv DYLD_INSERT_LIBRARIES libft_malloc.so
setenv DYLD_FORCE_FLAT_NAMESPACE 1 
cat src/*.c
