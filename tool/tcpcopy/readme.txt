���ĵ�����tcpcopy-0.9.8.tar.gz���Թ���

�����ϻ�����Ի��Ͼ�ִ�����±��밲װ����:
[���롢��װ]
work�˺��£�
sh autogen.sh
./configure --prefix=/home/work/tcpcopy
make
make install

root�˺���:
cd /home/work/tcpcopy/bin/
chown root.root *
chmod a+s *


[�������Ի��ϵ�intercept]
1. lsmod | grep ip_queue
���û�ҵ����ͣ�
modprobe ip_queue 

2. һ��Ҫ���������Ի��ϵ�intercept�����������ϻ��ϵ�tcpcopy����������tcpcopy�޷�����
sudo iptables -I OUTPUT -p tcp --sport  8501 -j QUEUE 
(8501�ǲ��Ի���Ӧ�ý�����Ķ˿ں�)

3. 
/home/work/tcpcopy/bin/intercept

���������ϻ��ϵ�tcpcopy��
4. /home/work/tcpcopy/bin/tcpcopy -x 8501-10.52.176.12:8510 -n 3
(8501�����ϻ��Ľ��̶˿�; 10.52.176.12:8510�ǲ��Ի���ip��˿�; -n 3�������������3�������������Ի�)

-----------------------------
��������iptables������Ӧ�����������Իᵼ������˿����Ӳ�ͨ(����telnet���ض˿ڳ���)
Ҫɾ������iptables rule�ķ������£�
��iptables -L -n -v���Կ������е�rule:
[root@st01-sw-bbqa01.st01.baidu.com ~]# iptables -L -n -v
Chain INPUT (policy ACCEPT 4209K packets, 598M bytes)
 pkts bytes target     prot opt in     out     source               destination         

Chain FORWARD (policy ACCEPT 0 packets, 0 bytes)
 pkts bytes target     prot opt in     out     source               destination         

Chain OUTPUT (policy ACCEPT 3251K packets, 704M bytes)
 pkts bytes target     prot opt in     out     source               destination         
15930 2554K QUEUE      tcp  --  *      *       0.0.0.0/0            0.0.0.0/0           tcp spt:8808 
 543K   50M QUEUE      tcp  --  *      *       0.0.0.0/0            0.0.0.0/0           tcp spt:8600 
 
 �������������OUTPUT������rule�Լ�line-number
 [root@st01-sw-bbqa01.st01.baidu.com ~]# iptables -L OUTPUT -n --line-numbers          
Chain OUTPUT (policy ACCEPT)
num  target     prot opt source               destination         
1    QUEUE      tcp  --  0.0.0.0/0            0.0.0.0/0           tcp spt:8808 
2    QUEUE      tcp  --  0.0.0.0/0            0.0.0.0/0           tcp spt:8600 
 
����line-numberɾ����Ӧ��rule
[root@st01-sw-bbqa01.st01.baidu.com ~]# iptables -D OUTPUT 2
[root@st01-sw-bbqa01.st01.baidu.com ~]# iptables -L OUTPUT -n --line-numbers
Chain OUTPUT (policy ACCEPT)
num  target     prot opt source               destination         
1    QUEUE      tcp  --  0.0.0.0/0            0.0.0.0/0           tcp spt:8808 