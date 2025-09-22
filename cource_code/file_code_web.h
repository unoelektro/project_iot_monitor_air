
String htmlPage = R"====(

<!DOCTYPE html>
<html lang="en">
<head>
  <title>Bootstrap 5 Example - Green and Yellow Theme</title>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/css/bootstrap.min.css" rel="stylesheet">
  <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/js/bootstrap.bundle.min.js"></script>
  <script src="https://cdn.jsdelivr.net/npm/chart.js"></script>
  <script src="https://cdnjs.cloudflare.com/ajax/libs/raphael/2.3.0/raphael.min.js"></script>
  <script src="https://toorshia.github.io/justgage/justgage.js"></script>
  <style>
	.font-title-web{
	  font-size: 20px;
	}
  
	.font-title-panel{
	  font-size: 15px;
	}
  
    .fs-custom {
      font-size: 70px;
    }
    body {
      background-color: #e8f5e9; /* Soft green background */
      color: #212529; /* Dark text for readability */
    }
    .card {
      background-color: #ffffff; /* White card background */
      color: #212529; /* Dark text */
      border: 1px solid #c8e6c9; /* Light green border */
      border-radius: 10px; /* Rounded corners */
      box-shadow: 0 2px 5px rgba(0, 0, 0, 0.1); /* Subtle shadow for depth */
    }
    .card-header {
      background-color: #fdd835; /* Bright yellow header */
      color: #212529; /* Dark text for contrast */
      font-weight: bold; /* Emphasize header text */
      border-bottom: 1px solid #c8e6c9; /* Subtle border matching theme */
    }
    .bg-primary {
      background-color: #43a047 !important; /* Vibrant green for main header */
      color: #ffffff !important; /* White text for contrast */
    }
    .bg-warning {
      background-color: #fdd835 !important; /* Bright yellow for highlight */
      color: #212529; /* Dark text */
    }
  </style>
</head>
<body>

<div class="container-fluid p-2 bg-primary text-center">
  <h3 class="font-title-web">Project IoT ESP8266</h3>
</div>
  
<div class="container mt-3">


   <div class="row mt-3">
    <div class="col-6">
      <div class="card">
        <h3 class="card-header p-3 font-title-panel">Debit Air</h3>
        <div class="card-body">
          <div id="gauge1" style="width:100%;height:100px;"></div>
        </div>
		<h3 class="card-header p-3 font-title-panel text-center"> Ltr/Mnt </h3>
      </div>
    </div>
	
    <div class="col-6">
      <div class="card">
        <h3 class="card-header p-3 font-title-panel">Suhu</h3>
        <div class="card-body">
          <div id="gauge2" style="width:100%;height:100px;"></div>
        </div>
		<h3 class="card-header p-3 font-title-panel text-center"> Celcius </h3>
      </div>
    </div>
  </div>
  
  <div class="row mt-3 mb-3">
    <div class="col-sm-12">
      <div class="card">
        <h3 class="card-header p-3 font-title-panel">Informasi Sensor</h3>
        <div class="card-body">
		
		<form>
		
		  <div class="form-group row">
			<label class="col-3 col-form-label fw-bold">Debit Air</label>
			<div class="col-5">
			  <input type="text" class="form-control text-center fw-bold" id="val_1" placeholder="0.0" readonly>
			</div>
			<label class="col-3 col-form-label fw-bold">  LPM</label>
		  </div>
		  
		  <div class="form-group row mt-2">
			<label class="col-3 col-form-label fw-bold">Suhu</label>
			<div class="col-5">
			  <input type="text" class="form-control text-center fw-bold" id="val_2" placeholder="0.0" readonly>
			</div>
			<label class="col-3 col-form-label fw-bold">  Celcius</label>
		  </div>
		  
		  <div class="form-group row mt-2">
			<label class="col-3 col-form-label fw-bold">Volume</label>
			<div class="col-5">
			  <input type="text" class="form-control text-center fw-bold" id="val_3" placeholder="0.0" readonly>
			</div>
			<label class="col-3 col-form-label fw-bold">  Liter</label>
		  </div>
		  
		  <div class="form-group row mt-2">
			<label class="col-3 col-form-label fw-bold">Status</label>
			<div class="col-8">
			  <textarea class="form-control" id="status" rows="3"></textarea>
			</div>
		  </div>
		  
		  
		</form>
		
        </div>
      </div>
    </div>
  </div>
  
  
</div>


    <script>
	  var g1 = null ;
	  var g2 = null ;
      document.addEventListener("DOMContentLoaded", function(event) {
        // Gauge 1
        g1 = new JustGage({
          id: "gauge1",
          value: 8,
          min: 0,
          max: 8,
		  donut: true,
          title: "Gauge Lainnya",
          label: "",
          titleFontColor: "#000",
          valueFontColor: "#000",
          labelFontColor: "#000",
          refreshAnimationTime: 1000
        });
        
        // Gauge 2
        g2 = new JustGage({
          id: "gauge2",
          value: 70,
          min: 0,
          max: 70,
		  donut: true,
          title: "Gauge Lainnya",
          label: "",
          titleFontColor: "#000",
          valueFontColor: "#000",
          labelFontColor: "#000",
          refreshAnimationTime: 1000
        });

      });
    </script>

<script>
	
        function loadData() {
            var xhr = new XMLHttpRequest();
            xhr.onreadystatechange = function() {
				
				try{
					console.log("Respon DiTerima : " + this.readyState);
					if (this.readyState == 4 && this.status == 200) {
						console.log("Text Respon : " + this.responseText );
						var data = this.responseText.split('x');
						//
						g1.refresh(parseFloat(data[0]));
						g2.refresh(parseFloat(data[1]));
						//
						document.getElementById("val_1").value = data[0];
						document.getElementById("val_2").value = data[1];
						document.getElementById("val_3").value = data[2];
						//
						document.getElementById("status").value = data[3];
					}
				}catch(e){
					console.log("Error...: " + e );
				}
            };
			
			var str_url = "/get" ;
			console.log("Mengirim request url : " + str_url);
            xhr.open("GET", str_url , true);
            xhr.send();
        }

        setInterval(loadData, 100);
    </script>
	


</body>
</html>

)====";




String htmlPage_Tablet = R"====(

<!DOCTYPE html>
<html lang="en">
<head>
  <title>Bootstrap 5 Example - Green and Yellow Theme</title>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/css/bootstrap.min.css" rel="stylesheet">
  <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/js/bootstrap.bundle.min.js"></script>
  <script src="https://cdn.jsdelivr.net/npm/chart.js"></script>
  <script src="https://cdnjs.cloudflare.com/ajax/libs/raphael/2.3.0/raphael.min.js"></script>
  <script src="https://toorshia.github.io/justgage/justgage.js"></script>
  <style>
	.font-title-web{
		font-size: 35px;
		padding-top: 15px;
		padding-bottom: 15px;
	}
  
	.font-title-panel{
	  font-size: 20px;
	}
  
    .fs-custom {
      font-size: 70px;
    }
    body {
      background-color: #e8f5e9; /* Soft green background */
      color: #212529; /* Dark text for readability */
    }
    .card {
      background-color: #ffffff; /* White card background */
      color: #212529; /* Dark text */
      border: 1px solid #c8e6c9; /* Light green border */
      border-radius: 10px; /* Rounded corners */
      box-shadow: 0 2px 5px rgba(0, 0, 0, 0.1); /* Subtle shadow for depth */
    }
    .card-header {
      background-color: #fdd835; /* Bright yellow header */
      color: #212529; /* Dark text for contrast */
      font-weight: bold; /* Emphasize header text */
      border-bottom: 1px solid #c8e6c9; /* Subtle border matching theme */
    }
    .bg-primary {
      background-color: #43a047 !important; /* Vibrant green for main header */
      color: #ffffff !important; /* White text for contrast */
    }
    .bg-warning {
      background-color: #fdd835 !important; /* Bright yellow for highlight */
      color: #212529; /* Dark text */
    }
  </style>
</head>
<body>

<div class="container-fluid p-2 bg-primary text-center">
  <h3 class="font-title-web">Project IoT ESP8266</h3>
</div>
  
<div class="container mt-3">


   <div class="row mt-3">
    <div class="col-6">
      <div class="card">
        <h3 class="card-header p-3 font-title-panel">Debit Air</h3>
        <div class="card-body">
          <div id="gauge1" style="width:100%;height:100px;"></div>
        </div>
		<h3 class="card-header p-3 font-title-panel text-center"> Ltr/Mnt </h3>
      </div>
    </div>
	
    <div class="col-6">
      <div class="card">
        <h3 class="card-header p-3 font-title-panel">Suhu</h3>
        <div class="card-body">
          <div id="gauge2" style="width:100%;height:100px;"></div>
        </div>
		<h3 class="card-header p-3 font-title-panel text-center"> Celcius </h3>
      </div>
    </div>
  </div>
  
  <div class="row mt-3 mb-3">
    <div class="col-sm-12">
      <div class="card">
        <h3 class="card-header p-3 font-title-panel">Informasi Sensor</h3>
        <div class="card-body">
		
		<form>
		
		  <div class="form-group row">
			<label class="col-3 col-form-label fw-bold">Debit Air</label>
			<div class="col-5">
			  <input type="text" class="form-control text-center fw-bold" id="val_1" placeholder="0.0" readonly>
			</div>
			<label class="col-3 col-form-label fw-bold">  LPM</label>
		  </div>
		  
		  <div class="form-group row mt-2">
			<label class="col-3 col-form-label fw-bold">Suhu</label>
			<div class="col-5">
			  <input type="text" class="form-control text-center fw-bold" id="val_2" placeholder="0.0" readonly>
			</div>
			<label class="col-3 col-form-label fw-bold">  Celcius</label>
		  </div>
		  
		  <div class="form-group row mt-2">
			<label class="col-3 col-form-label fw-bold">Volume</label>
			<div class="col-5">
			  <input type="text" class="form-control text-center fw-bold" id="val_3" placeholder="0.0" readonly>
			</div>
			<label class="col-3 col-form-label fw-bold">  Liter</label>
		  </div>
		  
		  <div class="form-group row mt-2">
			<label class="col-3 col-form-label fw-bold">Status</label>
			<div class="col-8">
			  <textarea class="form-control" id="status" rows="3"></textarea>
			</div>
		  </div>
		  
		  
		</form>
		
        </div>
      </div>
    </div>
  </div>
  
  
</div>


    <script>
	  var g1 = null ;
	  var g2 = null ;
      document.addEventListener("DOMContentLoaded", function(event) {
        // Gauge 1
        g1 = new JustGage({
          id: "gauge1",
          value: 8,
          min: 0,
          max: 8,
		  donut: true,
          title: "Gauge Lainnya",
          label: "",
          titleFontColor: "#000",
          valueFontColor: "#000",
          labelFontColor: "#000",
          refreshAnimationTime: 1000
        });
        
        // Gauge 2
        g2 = new JustGage({
          id: "gauge2",
          value: 70,
          min: 0,
          max: 70,
		  donut: true,
          title: "Gauge Lainnya",
          label: "",
          titleFontColor: "#000",
          valueFontColor: "#000",
          labelFontColor: "#000",
          refreshAnimationTime: 1000
        });

      });
    </script>

<script>
	
        function loadData() {
            var xhr = new XMLHttpRequest();
            xhr.onreadystatechange = function() {
				
				try{
					console.log("Respon DiTerima : " + this.readyState);
					if (this.readyState == 4 && this.status == 200) {
						console.log("Text Respon : " + this.responseText );
						var data = this.responseText.split('x');
						//
						g1.refresh(parseFloat(data[0]));
						g2.refresh(parseFloat(data[1]));
						//
						document.getElementById("val_1").value = data[0];
						document.getElementById("val_2").value = data[1];
						document.getElementById("val_3").value = data[2];
						//
						document.getElementById("status").value = data[3];
					}
				}catch(e){
					console.log("Error...: " + e );
				}
            };
			
			var str_url = "/get" ;
			console.log("Mengirim request url : " + str_url);
            xhr.open("GET", str_url , true);
            xhr.send();
        }

        setInterval(loadData, 100);
    </script>
	


</body>
</html>

)====";