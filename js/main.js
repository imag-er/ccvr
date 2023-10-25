// 动画的主要逻辑部分


// 获取dom

var dom = document.getElementById('chart-container');

// 创建echart
var myChart = echarts.init(dom, null, {
  renderer: 'canvas',
  useDirtyRect: false
});
var option;

var dataIdx = 0; // 用于跟踪当前显示的data索引

$.getJSON("data/mapstyle.json", function (map_style) {
  // 读取json
  $.getJSON("data/shenyang11.json", function (data) {
    

    function updateChartData() {
      // 设置echart样式
      myChart.setOption(
        (option = {
          bmap: {
            center: [123.38, 41.8], // 百度地图中心
            zoom: 10, // 缩放
            roam: true, // 是否能移动 缩放
            mapStyle: {
              // 详细风格
              // 这里把几乎所有东西设为了灰色
              styleJson: map_style
            }
          },
          series: [
            {
              type: 'lines', // 线图
              coordinateSystem: 'bmap', // 使用百度地图坐标系
              polyline: true, // 多线段
              data: data.slice(0 ,dataIdx), // 使用当前索引的数据
              silent: true,
              lineStyle: { // 线style
                color: 'rgb(200, 35, 45)',
                opacity: 0.5,
                width: 5
              },
              progressiveThreshold: 500,
              progressive: 200
            }
          ]
        })
      );
      
      // 增加索引，准备下一个数据
      dataIdx = (dataIdx + 1) % (data.length-10);
    }

    // 初始化显示第一个数据
    updateChartData();

    // 设置定时器，每2秒更新一次数据
    setInterval(updateChartData, 500);
  });
});

if (option && typeof option === 'object') {
  myChart.setOption(option);
}

window.addEventListener('resize', myChart.resize);
