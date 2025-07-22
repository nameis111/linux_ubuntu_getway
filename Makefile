
# $^： 依赖列表
# $@： 目标名
# -I:  给gcc配置包含的查看路径
# -g:  开启gdb的debug调试(生成的二进制文件中包含调试信息)
# -o0:  禁用优化(确保调试一致性)
# -Wall: 显示所有警告
# -l   library   指定用到的下载的库


CC:=gcc
CFLAGS:= -g -o0 -Wall			#开启debug调试

log:= thirdparty/log/log.h thirdparty/log/log.c
log_test: test/log_test.c  $(log)
	-gcc $^ -o $@ -I thirdparty
	-./$@
	-rm $@


json:= thirdparty/cJSON/cJSON.c thirdparty/cJSON/cJSON.h
json_test: test/json_test.c $(json) $(log)
	-$(CC) $(CFLAGS)  $^ -o $@ -I thirdparty 
#	-./$@
#	-rm $@


app_common:= app/app_common.h app/app_common.c
app_common_test: test/app_common_test.c $(app_common) $(log)
	-$(CC)  $^ -o $@ -I thirdparty  -I app
	-./$@
	-rm $@


app_message:= app/app_message.h app/app_message.c
app_message_test: test/app_message_test.c $(app_common) $(app_message) $(log) $(json)
	-$(CC)  $^ -o $@ -I thirdparty  -I app
	-./$@
	-rm $@


mqtt_test: test/mqtt_test.c
	-$(CC) $^ -o $@ -lpaho-mqtt3c
	-./$@
	-rm $@

app_mqtt:=app/app_mqtt.c  app/app_mqtt.h
app_mqtt_test: test/app_mqtt_test.c $(app_mqtt) $(log) 
	-$(CC) $^ -o $@ -I thirdparty -I app -lpaho-mqtt3c
	-./$@
	-rm $@
