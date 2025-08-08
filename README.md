# Cryptor

A text encryption/decryption utility using salted keys and bitwise Vigenère cipher.

```
>_ cryptor -h                                           # output help
>_ cryptor -e ./encrypt_me                              # outputs default encryption to stdout
>_ cryptor -e secret_key ./encrypt_me                   # outputs encryption to stdout
>_ cryptor -d secret_key ./decrypt_me                   # outputs decryption to stdout
>_ cryptor -e secret_key ./encrypt_me > ./decrypt me    # outputs encryption to file
```

Since secret keys can easily be logged, this utility
should not be used seriously for critical applications.
I built this in about 24 hours to learn more about C.

TODO: Test edge cases: very long keys, missing arguments, empty files
