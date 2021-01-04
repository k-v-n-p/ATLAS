var x,y,z;
function loadlocation() {
    $.getJSON("https://api.thingspeak.com/channels/1019289/fields/1/last.json?api_key=SI2ZF7IE3J6A13YI", function(result){  
        var m = result;
        x=Number(m.field1);
        //alert(x);
    });

    $.getJSON("https://api.thingspeak.com/channels/1019289/fields/2/last.json?api_key=SI2ZF7IE3J6A13YI", function(result){
        var m = result;
        y=Number(m.field2);
    });
}
window.setInterval(function(){
    loadlocation();
    console.log('x '+ x + '\n');
    console.log('y '+ y + '\n');
}, 1000);