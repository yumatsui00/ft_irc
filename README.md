# Webserv

##usage
```
make; ./ircserv <Port Num> <Server Pass>

ex) ./ircserv 5000 0000
```

Server 立ち上げ後、別のターミナルを開き、
```
nc 127.0.0.1 <Port Num>
```

または、irssi を開いた後に、

```
/connect 127.0.0.1 <Port Num> <Server Pass>
```

でサーバーに接続。
