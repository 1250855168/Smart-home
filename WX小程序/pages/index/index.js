// pages/index/index.js

Page({
  data: {
    temperature: 0,
    humidity: 0,
    lightIntensity: 0,
    lightStatus: false,
    fanStatus: false,
    alarmStatus: false
  },

  // 监听页面加载事件
  onLoad: function() {
    // 模拟接收 MQTT 数据包，并更新页面数据
    this.receiveMqttData();
  },

  // 模拟接收 MQTT 数据包，并更新页面数据
  receiveMqttData: function() {
    // 在这里编写接收 MQTT 数据包的逻辑，假设数据包格式如下：
    const mqttData = {
      temperature: 25,
      humidity: 50,
      lightIntensity: 100,
      lightStatus: true,
      fanStatus: false,
      alarmStatus: true
    };

    this.setData({
      temperature: mqttData.temperature,
      humidity: mqttData.humidity,
      lightIntensity: mqttData.lightIntensity,
      lightStatus: mqttData.lightStatus,
      fanStatus: mqttData.fanStatus,
      alarmStatus: mqttData.alarmStatus
    });
  },

  // 监听灯光开关变化事件
  switchLight: function(event) {
    const status = event.detail.value;
    this.setData({
      lightStatus: status
    });
    this.publishStatus('light', status);
  },

  // 监听风扇开关变化事件
  switchFan: function(event) {
    const status = event.detail.value;
    this.setData({
      fanStatus: status
    });
    this.publishStatus('fan', status);
  },

  // 监听报警器开关变化事件
  switchAlarm: function(event) {
    const status = event.detail.value;
    this.setData({
      alarmStatus: status
    });
    this.publishStatus('alarm', status);
  },

  // 发布状态到 MQTT 服务器
  publishStatus: function(topic, status) {
    // 在这里编写发布状态到 MQTT 服务器的逻辑
    // 例如使用 MQTT.js 库进行发布
  }
});

