var DateJs = {};

DateJs.DisplayWeek = function (date) {
	document.getElementById('weekDisplay').innerHTML = 
			DateJs.GetWeeklyDisplay(DateJs.GetFirstDayOfTheWeek(date), 
								  DateJs.GetLastDayOfTheWeek(date));
}

DateJs.GetWeeklyDisplay = function (first, last) {
	var output;
	if(first.getMonth() == last.getMonth()) {
		output = DateJs.GetMonthString(first.getMonth()) + ' ' 
									 + first.getDate() + " - " 
									 + last.getDate() + ", " 
									 + first.getFullYear();
	}
	else if(first.getMonth() != last.getMonth()){
		output = DateJs.GetMonthString(first.getMonth()) + ' ' + first.getDate() + " - " + 
				 DateJs.GetMonthString(last.getMonth()) + ' ' + last.getDate() + ", " + first.getFullYear();
	}
	return output;
}

DateJs.DisplayDay = function (date) {
	document.getElementById('dateDisplay').innerHTML = DateJs.GetDailyDisplay();
}

DateJs.GetDailyDisplay = function() {
	var output = DateJs.GetDay(DateUpdater.current.getDay()) + "   " + 
				 DateJs.GetMonthString(DateUpdater.current.getMonth()) + ' ' + 
				 DateUpdater.current.getDate() + ", " + 
				 DateUpdater.current.getFullYear();
	return output;
};

DateJs.GetMonthString = function (month) {
	var monthNames = ["January", "February", "March", "April", "May", "June",
					  "July", "August", "September", "October", "November", "December"];	
	return monthNames[month];
}

DateJs.GetDay = function(day) {
	var dayNames = ["Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"];
	return dayNames[day];
}

DateJs.GetFirstDayOfTheWeek = function (date) {
	var curr = new Date(date);
	var first = curr.getDate() - curr.getDay();
	curr.setHours(0);
	curr.setMinutes(0);
	curr.setSeconds(0);
	return new Date(curr.setDate(first))
}

DateJs.GetLastDayOfTheWeek = function (date) {	
	var first = new Date(DateJs.GetFirstDayOfTheWeek(date));
	var last = first.getDate() + 6;
	first.setHours(0);
	first.setMinutes(0);
	first.setSeconds(1);
	return new Date(first.setDate(last));
}


DateJs.GetDateFromJSON = function (dateTime) {
	var dateTimeArray = dateTime.split(" ");
	return dateTimeArray[0];
};

DateJs.ConvertJSONToDateTimeObject  = function (time) {
	var dateTimeArray = time.split(" ");
	var dateArray = dateTimeArray[0].split("-");
	var timeArray = dateTimeArray[1].split(":");
	return new Date(Number(dateArray[0]), Number(dateArray[1])-1, Number(dateArray[2]), 
					Number(timeArray[0]), Number(timeArray[1]), Number(1));
};

DateJs.IsDataFromToday = function (jsonDate) {	
	return DateJs.GetDateFromJSON(jsonDate) == DateJs.GetCurrentDate();	
};

DateJs.GetCurrentDate = function () {	
	var day = DateUpdater.current.getDate();
	if(day < 10) 
		day = '0' + day;
	var date = DateUpdater.current.getFullYear() + '-' + (DateUpdater.current.getMonth()+1) + '-' + day;
	return date;
};