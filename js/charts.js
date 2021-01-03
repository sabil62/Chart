var ctxBinLevel = document.getElementById("bin-level").getContext("2d");
var ctxHumidity = document.getElementById("humidity").getContext("2d");
var ctxTemperature = document.getElementById("temperature").getContext("2d");

var chart = new Chart(ctxBinLevel, {
  type: "bar",
  data: {
    labels: ["Level"],
    datasets: [
      {
        label: "level",
        data: [7],
        backgroundColor: ["rgba(54, 162, 235, 0.65)"],
      },
    ],
  },
  options: {},
});

var chart = new Chart(ctxHumidity, {
  type: "doughnut",
  data: {
    labels: ["Humidity"],
    datasets: [
      {
        label: "Humidity",
        data: [73, 27],
        backgroundColor: [
          "rgba(54, 162, 235, 0.65)",
          "rgba(255, 206, 86, 0.65)",
        ],
      },
    ],
  },
  options: {},
});

var chart3 = new Chart(ctxTemperature, {
  type: "line",
  data: {
    labels: ["9:00", "9:05", "9:10", "9:15", "9:20", "9:25", "9:30"],
    datasets: [
      {
        label: "temperature",
        data: [13, 13.5, 14, 15, 17, 16, 13],
        backgroundColor: ["rgba(255,206,90,0.65)"],
      },
    ],
  },
  options: {},
});

// for clock----------------------------
let clock = () => {
  let date = new Date();
  let hrs = date.getHours();
  let mins = date.getMinutes();
  let secs = date.getSeconds();
  let period = "AM";
  if (hrs == 0) {
    hrs = 12;
  } else if (hrs >= 12) {
    hrs = hrs - 12;
    period = "PM";
  }
  hrs = hrs < 10 ? "0" + hrs : hrs;
  mins = mins < 10 ? "0" + mins : mins;
  secs = secs < 10 ? "0" + secs : secs;

  let time = `${hrs}:${mins}:${secs}:${period}`;
  document.getElementById("clock").innerText = time;
  setTimeout(clock, 1000);
};

clock();
