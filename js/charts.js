var ctxBinLevel = document.getElementById("bin-level").getContext("2d");
var ctxHumidity = document.getElementById("humidity").getContext("2d");

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
