本文档仅对tcpcopy-0.9.8.tar.gz测试过。

在线上机与测试机上均执行如下编译安装步骤:
[编译、安装]
work账号下：
sh autogen.sh
./configure --prefix=/home/work/tcpcopy
make
make install

root账号下:
cd /home/work/tcpcopy/bin/
chown root.root *
chmod a+s *


[启动测试机上的intercept]
1. lsmod | grep ip_queue
如果没找到，就：
modprobe ip_queue 

2. 一定要先启动测试机上的intercept，再启动线上机上的tcpcopy，否则线上tcpcopy无法启动
sudo iptables -I OUTPUT -p tcp --sport  8501 -j QUEUE 
(8501是测试机上应用进程起的端口号)

3. 
/home/work/tcpcopy/bin/intercept

【启动线上机上的tcpcopy】
4. /home/work/tcpcopy/bin/tcpcopy -x 8501-10.52.176.12:8510 -n 3
(8501是线上机的进程端口; 10.52.176.12:8510是测试机的ip与端口; -n 3会把线上请求以3倍的量发给测试机)

-----------------------------
由于配了iptables，让响应包丢掉，所以会导致这个端口连接不通(包括telnet或监控端口程序)
要删除这条iptables rule的方法如下：
用iptables -L -n -v可以看到所有的rule:
[root@st01-sw-bbqa01.st01.baidu.com ~]# iptables -L -n -v
Chain INPUT (policy ACCEPT 4209K packets, 598M bytes)
 pkts bytes target     prot opt in     out     source               destination         

Chain FORWARD (policy ACCEPT 0 packets, 0 bytes)
 pkts bytes target     prot opt in     out     source               destination         

Chain OUTPUT (policy ACCEPT 3251K packets, 704M bytes)
 pkts bytes target     prot opt in     out     source               destination         
15930 2554K QUEUE      tcp  --  *      *       0.0.0.0/0            0.0.0.0/0           tcp spt:8808 
 543K   50M QUEUE      tcp  --  *      *       0.0.0.0/0            0.0.0.0/0           tcp spt:8600 
 
 用如下命令，看到OUTPUT下所有rule以及line-number
 [root@st01-sw-bbqa01.st01.baidu.com ~]# iptables -L OUTPUT -n --line-numbers          
Chain OUTPUT (policy ACCEPT)
num  target     prot opt source               destination         
1    QUEUE      tcp  --  0.0.0.0/0            0.0.0.0/0           tcp spt:8808 
2    QUEUE      tcp  --  0.0.0.0/0            0.0.0.0/0           tcp spt:8600 
 
根据line-number删除对应的rule
[root@st01-sw-bbqa01.st01.baidu.com ~]# iptables -D OUTPUT 2
[root@st01-sw-bbqa01.st01.baidu.com ~]# iptables -L OUTPUT -n --line-numbers
Chain OUTPUT (policy ACCEPT)
num  target     prot opt source               destination         
1    QUEUE      tcp  --  0.0.0.0/0            0.0.0.0/0           tcp spt:8808 