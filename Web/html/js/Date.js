var DateJs = {};

DateJs.DisplayMonth = function () {
	document.getElementById('monthDisplay').innerHTML = DateJs.GetMonthlyDisplay();
}

DateJs.GetMonthlyDisplay = function() {
	var output = DateJs.GetMonthString(DateUpdater.current.getMonth()) + ' ' + 
				 DateUpdater.current.getFullYear();
	return output;
}

DateJs.DisplayWeek = function () {
	document.getElementById('weekDisplay').innerHTML = 
			DateJs.GetWeeklyDisplay(DateJs.GetFirstDayOfTheWeek(DateUpdater.current), 
								  DateJs.GetLastDayOfTheWeek(DateUpdater.current));
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

DateJs.DisplayDay = function () {
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
	var monthNames = ["Jan", "Feb", "Mar", "Apr", "May", "Jun",
					  "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"];	
	return monthNames[month];
}

DateJs.GetDay = function(day) {
	var dayNames = ["Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"];
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

DateJs.GetLastDateOfTheMonth = function (date) {	
	var curr = new Date(date);
	var last;
	if(curr.getMonth() < 7) {
		if((curr.getMonth() % 2) == 0)
			curr.setDate(31);
		else {
			if(curr.getMonth() == 1) {
				if((curr.getFullYear() % 4) == 0)
					curr.setDate(29);
				else
					curr.setDate(28);
			}
			else
				curr.setDate(30);
		}
	}
	else {
		if((curr.getMonth() % 2) != 0)
			curr.setDate(31);
		else
			curr.setDate(30);

	}	
	curr.setHours(0);
	curr.setMinutes(0);
	curr.setSeconds(1);
	return curr;
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