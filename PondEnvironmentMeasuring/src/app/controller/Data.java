package app.controller;

public class Data {

	int hours, seconds, minutes, day, month, year;
	double pond_temp, weather_temp, light;
	
	public Data(String rawData) {
		super();
		String[] results = rawData.split(",");
		
		hours = Integer.parseInt(results[0]);
		minutes = Integer.parseInt(results[1]);
		seconds = Integer.parseInt(results[2]);
		day = Integer.parseInt(results[3]);
		month = Integer.parseInt(results[4]);
		year = Integer.parseInt(results[5]);
		pond_temp = Double.parseDouble(results[6]);
		weather_temp = Double.parseDouble(results[7]);
		light = Double.parseDouble(results[8]);
		
	}

	public int getHours() {
		return hours;
	}

	public int getSeconds() {
		return seconds;
	}

	public int getMinutes() {
		return minutes;
	}

	public int getDay() {
		return day;
	}

	public int getMonth() {
		return month;
	}

	public int getYear() {
		return year;
	}

	public double getPond_temp() {
		return pond_temp;
	}

	public double getWeather_temp() {
		return weather_temp;
	}

	public double getLight() {
		return light;
	}

}
