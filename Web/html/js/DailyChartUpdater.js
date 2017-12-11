
var DailyUpdater = {};

DailyUpdater.Update = function() {
	var json = $.ajax({				 
		url: "/html/php/DailyMeasurement.php",
		dataType: "json",
		success: function(jsonstring) {
			for(var i = 0 ; i < Sensor.sensorArray.length; i++) {
				var sensorData = DailyUpdater.GetChartData(jsonstring, Sensor.sensorArray[i]);
				DailyUpdater.DrawChart(sensorData, Sensor.sensorArray[i]);
			}			
		},
		error: function(xhr, status, error) {					
			alert(error);
		}				
	}).responseText;
};

DailyUpdater.GetChartData = function (jsonData, choice) {
	var data = new google.visualization.DataTable();
	data.addColumn('datetime', 'Time');
	data.addColumn('number', choice);
	for(var i = 0; i < jsonData.length; i++) {
		if(DateJs.IsDataFromToday(jsonData[i].Time)) {
			var t = DateJs.ConvertJSONToDateTimeObject(jsonData[i].Time);
			switch(choice) {
				case Sensor.Temperature:					
					data.addRow([t, Number(jsonData[i].Temperature)]);
					break;
				case Sensor.Humidity:
					data.addRow([t, Number(jsonData[i].Humidity)]);
					break;
				case Sensor.SoilMoisture:
					data.addRow([t, Number(jsonData[i].SoilMoisture)]);
					break;
				case Sensor.UV:
					data.addRow([t, Number(jsonData[i].UV)]);
					break;
			}
		}
	}
	return data;
};

DailyUpdater.DrawChart = function(chartData, className) {
	var options = {		
		legend: { position: 'none'},
		backgroundColor: "transparent",
		hAxis: {
			gridlines: {color: '#333', count: 8},
			minorGridlines: {count: 2},
			maxValue: new Date(DateUpdater.current.getFullYear(), 
							   (DateUpdater.current.getMonth()), 
							    DateUpdater.current.getDate(), 
								23, 59, 59),
			minValue: new Date(DateUpdater.current.getFullYear(), 
							   (DateUpdater.current.getMonth()), 
							    DateUpdater.current.getDate(), 
								0, 0, 0)
		},
		vAxis: {
			title: className
		}
	};
	var chart = new google.visualization.LineChart(document.getElementById(className));
	chart.draw(chartData, options);
};