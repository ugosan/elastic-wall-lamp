const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>

  <head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, maximum-scale=1.0, minimum-scale=1.0, initial-scale=1.0">
    <title>Elastic Lamp</title>
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/bulma/0.7.5/css/bulma.min.css">

    <script src="https://code.jquery.com/jquery-2.2.4.min.js" integrity="sha256-BbhdlvQf/xTY9gja0Dq3HiwQF8LaCRTXxZKRutelT44=" crossorigin="anonymous"></script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/tinyColorPicker/1.1.1/jqColorPicker.min.js"></script>
    <style>
      body div{
          max-width: 100%;
          overflow-x: hidden;
      }
      </style>
  </head>

  <body>


    <section class="box">
      <div class="container">

        <div class="box has-text-centered is-12">
          <svg xmlns:dc="http://purl.org/dc/elements/1.1/" xmlns:cc="http://creativecommons.org/ns#" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#" xmlns:svg="http://www.w3.org/2000/svg" xmlns="http://www.w3.org/2000/svg" xmlns:sodipodi="http://sodipodi.sourceforge.net/DTD/sodipodi-0.dtd"
            xmlns:inkscape="http://www.inkscape.org/namespaces/inkscape" width="60mm" height="60mm" viewBox="0 0 102.19126 101.79368" version="1.1" id="svg8" inkscape:version="1.0.2 (e86c8708, 2021-01-15)" sodipodi:docname="test.svg">
              <g
                inkscape:label="Layer 1"
                inkscape:groupmode="layer"
                id="layer1"
                transform="translate(-3.3329767,-2.5673019)"
                style="opacity:1">
                <path
                  style="fill:#000000"
                  d="m 105.52424,55.898482 c 0,-8.56474 -5.31037,-16.052448 -13.301843,-18.966039 0.35136,-1.805164 0.53481,-3.610681 0.53481,-5.490986 0,-15.920861 -12.9533,-28.8741551 -28.87663,-28.8741551 -9.300984,0 -17.953564,4.460875 -23.390575,11.9768051 -2.672998,-2.073981 -5.955947,-3.210278 -9.381067,-3.210278 -8.451144,0 -15.32643,6.875639 -15.32643,15.326783 0,1.867253 0.333022,3.654778 0.958144,5.341056 -7.9449083,2.867025 -13.4076723,10.530764 -13.4076723,19.041184 0,8.60848 5.336117,16.13006 13.3635753,19.02283 -0.340783,1.78471 -0.526697,3.62621 -0.526697,5.48852 0,15.88488 12.92225,28.806778 28.806774,28.806778 9.32427,0 17.971558,-4.478868 23.377528,-12.025848 2.69134,2.11279 5.98205,3.27237 9.39377,3.27237 8.45114,0 15.32678,-6.87282 15.32678,-15.32396 0,-1.86761 -0.33302,-3.65725 -0.95815,-5.34388 7.944913,-2.86455 13.407683,-10.53041 13.407683,-19.04118"
                  id="path853" />
                <path
                  style="fill:#FED10A"
                  d="M 42.897004,17.61786 C 47.614349,10.748218 55.375107,6.6514099 63.695367,6.6514099 c 13.90897,0 25.22221,11.3160521 25.22221,25.2246691 0,1.701447 -0.15981,3.327047 -0.48613,4.957586 l -22.5612,19.767897 -22.360468,-10.19386 -4.365272,-9.320743 z"
                  id="bubbleC" />
                <path
                  style="fill:#DF4998;fill-opacity:1;fill-rule:nonzero;stroke:none;stroke-width:0.352778;stroke-opacity:1"
                  d="m 31.565782,15.108551 c 2.658534,0 5.244042,0.8763 7.337778,2.4765 L 35.546174,35.00804 20.22186,31.389951 c -0.486127,-1.321858 -0.731661,-2.732264 -0.731661,-4.203347 0,-6.659386 5.416197,-12.078053 12.075583,-12.078053"
                  id="path849" />
                <path
                  style="fill:#00A9E5;fill-opacity:1;fill-rule:nonzero;stroke:none;stroke-width:0.352778"
                  d="m 7.2844407,51.090472 c 0,-7.21924 4.7603833,-13.782321 11.6070943,-16.051035 l 16.817975,3.972983 3.947583,8.434212 -21.500041,19.43382 C 11.632075,64.396552 7.2844407,58.119572 7.2844407,51.090472"
                  id="path847" />
                <path
                  style="fill:#00BFB3;fill-opacity:1;fill-rule:nonzero;stroke:none;stroke-width:0.352778"
                  d="m 66.060037,89.335462 c -4.70993,6.94055 -12.508438,11.075458 -20.897494,11.075458 -13.946363,0 -25.292755,-11.346038 -25.292755,-25.290278 0,-1.71168 0.167217,-3.40325 0.493536,-5.03379 l 22.001339,-19.88432 22.449364,10.23197 4.97064,9.49783 z"
                  id="path845" />
                <path
                  style="fill:#10b13b;fill-opacity:1;fill-rule:nonzero;stroke:none;stroke-width:0.352778"
                  d="m 77.290727,91.831722 c -2.62573,0 -5.19854,-0.88089 -7.30004,-2.49661 l 3.33199,-17.36231 15.31161,3.58281 c 0.48613,1.32151 0.73202,2.73227 0.73202,4.20088 0,6.65939 -5.4162,12.07523 -12.07558,12.07523"
                  id="path843" />
                <path
                  style="fill:#0078A0;fill-opacity:1;fill-rule:nonzero;stroke:none;stroke-width:0.352778"
                  d="m 89.962147,71.901542 -16.85607,-3.94229 -4.47676,-8.55592 22.04685,-19.31494 c 6.53803,2.4765 10.895543,8.74607 10.895543,15.76211 0,7.22172 -4.760033,13.78727 -11.609563,16.05104"
                  id="path871" />
                <ellipse
                onclick="$('#path938').colorPicker({renderCallback: function($elm, toggled) {
                  onColorChange('A',this.color.colors.RND.rgb); 
                }})"
                style="fill-opacity:0;stroke:none;stroke-width:2.64583;stroke-opacity:1"
                  id="path938"
                  cx="20.719881"
                  cy="49.62534"
                  rx="14.741072"
                  ry="14.174108" />
                <ellipse
                  onclick="$('#path895').colorPicker({renderCallback: function($elm, toggled) {
                    onColorChange('B',this.color.colors.RND.rgb); 
                  }})"
                  style="fill-opacity:0;stroke:none;stroke-width:2.64583;stroke-opacity:1"
                  id="path895"
                  cx="29.980299"
                  cy="25.056885"
                  rx="9.1642084"
                  ry="12.030073" />
                  <ellipse
                  onclick="$('#path930').colorPicker({renderCallback: function($elm, toggled) {
                    onColorChange('C',this.color.colors.RND.rgb); 
                  }})"
                  style="fill-opacity:0;stroke:none;stroke-width:2.64583;stroke-opacity:1"
                  id="path930"
                  cx="62.67524"
                  cy="29.5926"
                  rx="22.489584"
                  ry="20.977678" />
                <ellipse
                onclick="$('#path932').colorPicker({renderCallback: function($elm, toggled) {
                  onColorChange('D',this.color.colors.RND.rgb); 
                }})"
                style="fill-opacity:0;stroke:none;stroke-width:2.64583;stroke-opacity:1"
                  id="path932"
                  cx="86.865715"
                  cy="57.56284"
                  rx="15.308036"
                  ry="9.0714283" />
                <ellipse
                onclick="$('#path934').colorPicker({renderCallback: function($elm, toggled) {
                  onColorChange('E',this.color.colors.RND.rgb); 
                }})"
                style="fill-opacity:0;stroke:none;stroke-width:2.64583;stroke-opacity:1"
                  id="path934"
                  cx="78.928215"
                  cy="81.186348"
                  rx="10.961308"
                  ry="6.9925594" />
                <ellipse
                onclick="$('#path936').colorPicker({renderCallback: function($elm, toggled) {
                  onColorChange('F',this.color.colors.RND.rgb); 
                }})"
                style="fill-opacity:0;stroke:none;stroke-width:2.64583;stroke-opacity:1"
                  id="path936"
                  cx="44.910355"
                  cy="75.516708"
                  rx="21.733631"
                  ry="23.434523" />
                
              </g>
            </svg>

        </div>

        <div class="box has-text-centered">
          <span class="button is-success is-selected ">A</span>
          <span class="button ">B</span>
          <span class="button ">C</span>
        </div>

      </div>
    </section>

    <script>
      var update = false;
      var bubble = "";
      var r = 0;
      var g = 0;
      var b = 0;

      function onColorChange(_bubble, _rgb) {
        
        bubble = _bubble;
        r = _rgb.r;
        g = _rgb.g;
        b = _rgb.b;

        console.info(`bubble=${bubble}&r=${r}&g=${g}&b=${b}`);
        
        if(update){
          try {
            var xhr = new XMLHttpRequest();
            xhr.open("POST", "/", true);
            xhr.setRequestHeader("Content-Type", "application/x-www-form-urlencoded; charset=UTF-8");
            xhr.send(`bubble=${bubble}&r=${r}&g=${g}&b=${b}`);
            update = false;
          } catch (error) {
            console.error(error);
          }
        }
      }

      setInterval(function(){ 
        update = !update;
      }, 500);

    </script>
  </body>

</html>

)=====";
