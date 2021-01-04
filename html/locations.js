var place;
function locations(latitude,longitude)  {
    if(distance(latitude, longitude,24.759636, 92.787895,"K") < 10)
    {
        /*place="9";
        ThingSpeak.setField(3, place);*/
        console.log("AT HOSTEL\n");
    }
    else if(distance(latitude, longitude, 24.759135, 92.788302,"K") < 10)
    {
        /*place="1";
        ThingSpeak.setField(3, place);*/
        console.log("H-8\n");
    }
    else if(distance(latitude, longitude, 24.758645, 92.788291,"K") < 10)
    {
        /*place="2";
        ThingSpeak.setField(3, place);*/
        console.log("H-4\n");
    }
    else if(distance(latitude, longitude, 24.757977, 92.788382,"K") < 10)
    {
        /*place="3";
        ThingSpeak.setField(3, place);*/
        console.log("Teapoint\n");
    }
    else if(distance(latitude, longitude, 24.757681, 92.787195,"K") < 10)
    {
        /*place="4";
        ThingSpeak.setField(3, place);*/
        console.log("PG\n");
    }
    else if(distance(latitude, longitude, 24.757032, 92.788426,"K") < 10)
    {
        /*place="5";
        ThingSpeak.setField(3, place);*/
        console.log("SAC\n");
    }
    else if(distance(latitude, longitude, 24.758024, 92.790308,"K") < 10)
    {
        /*place=6;
        ThingSpeak.writeField(970279,3,6,'PMB0WLGPBQ2CA921');*/
        console.log("NEW GALLERY\n");
    }
    return place;
}