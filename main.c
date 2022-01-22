#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "https.h"
#include "cJSON.h"

#define corpid      "your corpid"
#define corpsecret  "your corpsecret"
#define agentid     1000000     // app id

int main(int argc, char *argv[])
{
    cJSON *token_resp_json, *sendMsg_resp_json;
    char *url_format, *access_token, *message;
    char data[1024], response[4096], url[1024];
    int  i, ret, size;

    HTTP_INFO hi1, hi2;

    // Init http session. verify: check the server CA cert.
    http_init(&hi1, FALSE);
    http_init(&hi2, TRUE);

    // Get Token
    url_format = "https://qyapi.weixin.qq.com/cgi-bin/gettoken?corpid=%s&corpsecret=%s";
    sprintf(url,url_format,corpid,corpsecret);
    ret = http_get(&hi1, url, response, sizeof(response));
    token_resp_json = cJSON_Parse(response);
    access_token = cJSON_GetObjectItem(token_resp_json,"access_token")->valuestring;

    // 如果有参数，取第1个当作告警信息
    message = argc > 1 ? argv[1] : "烟雾浓度大于100";
    
    // Send Message
    url_format = "https://qyapi.weixin.qq.com/cgi-bin/message/send?access_token=%s";
    sprintf(url,url_format,access_token);

    cJSON *text = cJSON_CreateObject();
    cJSON_AddItemToObject(text,"content",cJSON_CreateString(message));
    sendMsg_resp_json = cJSON_CreateObject();
    cJSON_AddItemToObject(sendMsg_resp_json,"touser",cJSON_CreateString("@all"));
    cJSON_AddItemToObject(sendMsg_resp_json,"msgtype",cJSON_CreateString("text"));
    cJSON_AddItemToObject(sendMsg_resp_json,"agentid",cJSON_CreateNumber(agentid));
    cJSON_AddItemToObject(sendMsg_resp_json,"text",text);
    cJSON_AddItemToObject(sendMsg_resp_json,"safe",cJSON_CreateNumber(0));

    char *str_data = cJSON_Print(sendMsg_resp_json);
    sprintf(data,"%s",str_data);

    ret = http_post(&hi2, url, str_data, response, sizeof(response));
    printf("Send Weixin Message: %s \n", response);

    cJSON_Delete(sendMsg_resp_json);

error:

    http_close(&hi1);
    http_close(&hi2);

    return 0;
}
