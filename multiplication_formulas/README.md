# 客户端发送9*9计算结果给服务器

* 要点：连接关闭的时候，客户端shutdown write， 服务器read返回0，关闭连接。此时客户端read返回0，也可以安全关闭连接了。
