var accldiff;
var limit,dist;
var accX,accY,accZ;
var accx=new Array(3);
var accz=new Array(3);
function getaccl()  {
    $.getJSON("https://api.thingspeak.com/channels/1019289/fields/3/last.json?api_key=SI2ZF7IE3J6A13YI", function(result){
      var m = result;
      accX=Number(m.field3);
      console.log(accX+'\n');
    });
    /*$.getJSON("https://api.thingspeak.com/channels/1019289/fields/2/last.json?api_key=SI2ZF7IE3J6A13YI", function(result){
      var m = result;
      accY=Number(m.field2);
      console.log(accY);
      //alert(x);
    });*/
    $.getJSON("https://api.thingspeak.com/channels/1019289/fields/5/last.json?api_key=SI2ZF7IE3J6A13YI", function(result){
        var m = result;
      accZ=Number(m.field5);
      console.log(accZ+'\n');
      //alert(x);
    });
    $.getJSON("https://api.thingspeak.com/channels/970279/fields/6/last.json?api_key=SI2ZF7IE3J6A13YI", function(result){
      var m = result;
      dist=Number(m.field6);
      console.log(dist+'\n');
      //alert(x);
    });
    if(cnt===1) {
      accx[2]=accX;   accz[2]=accZ;
      cnt=cnt+1;
    }
    else if(cnt===2) {
      accx[1]=accx[2];    accz[1]=accz[2];
      accx[2]=accX;   accz[2]=accZ;
      cnt=cnt+1;
    }
    else  {
      accx[0]=accx[1];    accz[0]=accz[1];
      accx[1]=accx[2];    accz[1]=accz[2];
      accx[2]=accX;   accz[2]=accZ;
    }
    if(abs(accx[0]-accx[1])>accldiff || abs(accx[0]-accx[2])>accldiff || abs(accx[1]-accx[2])>accldiff) {
      var obj=loadlocation();
      var max=Math.max(abs(accx[0]-accx[1]),abs(accx[0]-accx[2]),abs(accx[1]-accx[2]));
      alert("Accident Detected");
    }
    if(abs(accz[0]-accz[1])>limit || abs(accz[0]-accz[2])>limit || abs(accz[1]-accz[2])>limit) {
      var obj=loadloction();
      var max=Math.max(abs(accz[0]-accz[1]),abs(accz[0]-accz[2]),abs(accz[1]-accz[2]));
    }
  }
