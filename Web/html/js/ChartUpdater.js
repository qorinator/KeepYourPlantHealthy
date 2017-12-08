const Sensor = {	
	Temperature : 'Temperature',
	Humidity : 'Humidity', 
	SoilMoisture : 'SoilMoisture',
	UV : 'UV',
};

Sensor.sensorArray = [Sensor.UV, Sensor.Temperature, Sensor.Humidity, Sensor.SoilMoisture];

var ChartUpdater = {};

ChartUpdater.Update = function() {
	var json = $.ajax({				 
		url: "/html/php/DailyMeasurement.php",
		dataType: "json",
		success: function(jsonstring) {
			for(var i = 0 ; i < Sensor.sensorArray.length; i++) {
				var sensorData = ChartUpdater.GetChartData(jsonstring, Sensor.sensorArray[i]);
				ChartUpdater.DrawChart(sensorData, Sensor.sensorArray[i]);
			}			
		},
		error: function(xhr, status, error) {					
			alert(error);
		}				
	}).responseText;
};

ChartUpdater.GetChartData = function (jsonData, choice) {
	var data = new google.visualization.DataTable();
	data.addColumn('datetime', 'Time');
	data.addColumn('number', choice);
	for(var i = 0; i < jsonData.length; i++) {
		if(ChartUpdater.IsDataFromToday(jsonData[i].Time)) {
			var t = ChartUpdater.ConvertJSONToDateTimeObject(jsonData[i].Time);
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

ChartUpdater.IsDataFromToday = function (jsonDate) {	
	return ChartUpdater.GetDateFromJSON(jsonDate) == ChartUpdater.GetCurrentDate();	
};

ChartUpdater.GetDateFromJSON = function (dateTime) {
	var dateTimeArray = dateTime.split(" ");
	return dateTimeArray[0];
};

ChartUpdater.GetCurrentDate = function () {	
	var day = DateUpdater.current.getDate();
	if(day < 10) 
		day = '0' + day;
	var date = DateUpdater.current.getFullYear() + '-' + (DateUpdater.current.getMonth()+1) + '-' + day;
	return date;
};

ChartUpdater.ConvertJSONToDateTimeObject  = function (time) {
	var dateTimeArray = time.split(" ");
	var dateArray = dateTimeArray[0].split("-");
	var timeArray = dateTimeArray[1].split(":");
	return new Date(Number(dateArray[0]), Number(dateArray[1])-1, Number(dateArray[2]), 
					Number(timeArray[0]), Number(timeArray[1]), Number(1));
};

ChartUpdater.DrawChart = function(chartData, className) {
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