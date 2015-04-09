var boilercontrollib = require('./build/Release/boilercontrol');

var offset;
if(process.argv.indexOf("-o") != -1){
    offset = process.argv[process.argv.indexOf("-o") + 1];
}

var boilercontrol;
if(!offset) {
    boilercontrol = new boilercontrollib.BoilerControl(0);
}
else
{
    boilercontrol = new boilercontrollib.BoilerControl(0, offset);
}
console.log("boilercontrol created: " + (boilercontrol != null));
boilercontrol.sendOnSignal();
boilercontrol.sendOffSignal();
