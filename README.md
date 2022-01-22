# WeXin Message Pusher

基于C实现的微信企业号消息推送工具


## 环境
请在 Linux 环境下编译

## 使用方法

1. 先下载代码并进入代码目录（国内推荐使用[Gitee](https://gitee.com/obiscr/wxmsg.git)，不为别的，就因为它快）
```bash
git clone https://github.com/obiscr/wxmsg.git
cd wxmsg
```

2. 然后打开 **main.c** 文件
首次打开，如果用编辑器的话，可能会提示43行报错，是因为 agendid 是 int 类型
而我写的是字符串。把自己的agendid替换掉就好了

在下面填入自己的企业号的 corpid，corpsecret，还有应用的 agentid
```
#define corpid      "your corpid" // your corpid  替换成自己企业号的 corpid
#define corpsecret  "your corpsecret" // your corpsecret  替换成自己企业号的 corpsecret
#define agentid     agentid     // agentid 替换成自己企业号应用的 agentid
```

假设修改完成之后，如下
```
#define corpid      "wxsdf789safdsfsdaf"
#define corpsecret  "msadfsafdsf-sadfsafsafasfasdf"
#define agentid     100001
```
然后保存即可。

3. 打开终端，进入 https_client 目录，执行如下命令，会把生成的二进制文件默认安装到 `/usr/local/bin/` 目录下面，
请确保此目录在环境变量中。

```bash
make 
sudo make install
```

4. 测试：打开终端，执行

```bash
wxmsg
```
或者
```bash
wxmsg 自定义消息
```
屏幕输出 `Send Weixin Message: {"errcode":0,"errmsg":"ok","invaliduser":""}` 则编译成功。
同时你的微信企业号也会收到刚才发送的消息。

# 常见问题

问题1：执行 **wxmsg** 提示：**wxmsg: command not found** ，
1. 请在终端执行 `echo $PATH` ，查看输出的内容是否包含 `/usr/local/bin/`，如果不包含，
请把 `/usr/local/bin/` 添加到环境变量。重新在终端执行 **wxmsg** 如果依旧提示 **wxmsg: command not found** ，请看第二步

2. 请检查 `/usr/local/bin/` 目录是否存在 **wxmsg**文件，不存在说明编译有问题没有生成二进制文件
或者是在 `make` 完成之后忘记执行 `sudo make install` ，请在终端再次执行 `sudo make install`。
然后 **wxmsg** 应该可以看到正常的输出信息了。

# 参考
+ [HISONA/https_client](https://github.com/HISONA/https_client)