var DateUpdater = {
	current: new Date(),
	todayDate: new Date()
};

DateUpdater.Increase = function(select) {
	if(DateUpdater.current < DateUpdater.todayDate) {
		switch(select) {
		case "Daily":			
			DateUpdater.current.setDate(DateUpdater.current.getDate() + 1);
			break;
		case "Weekly" :
			DateUpdater.current.setDate(DateUpdater.current.getDate() + 7);
			break;
		case "Monthly" :
			DateUpdater.current.setMonth(DateUpdater.current.getMonth() + 1);
			break;
		}	
	}	
};

DateUpdater.Decrease = function(select) {
	switch(select) {
	case "Daily":			
		DateUpdater.current.setDate(DateUpdater.current.getDate() - 1);
		break;
	case "Weekly" :
		DateUpdater.current.setDate(DateUpdater.current.getDate() - 7);
		break;
	case "Monthly" :
		DateUpdater.current.setMonth(DateUpdater.current.getMonth() - 1);
		break;
	}	
};
