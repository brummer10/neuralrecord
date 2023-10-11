function (event) {

    const meter = event.icon.find ('[mod-port-symbol=METER]');
    const state = event.icon.find ('[mod-port-symbol=STATE]');
    const popup = event.icon.find ('.popup');

    var position = "0";

    function log_meter (db) {
        var def = 0.000001; /* Meter deflection %age */

        if (db < -70.0) {
            def = 0.0000001;
        } else if (db < -60.0) {
            def = (db + 70.0) * 0.25;
        } else if (db < -50.0) {
            def = (db + 60.0) * 0.5 + 2.5;
        } else if (db < -40.0) {
            def = (db + 50.0) * 0.75 + 7.5;
        } else if (db < -30.0) {
            def = (db + 40.0) * 1.5 + 15.0;
        } else if (db < -20.0) {
            def = (db + 30.0) * 2.0 + 30.0;
        } else if (db < 6.0) {
            def = (db + 20.0) * 2.5 + 50.0;
        } else {
            def = 115.0;
        }

        return (Math.floor((def/115.0)* 100 ) ).toFixed(1);
    }

    function handle_event (symbol, value) {
        switch (symbol) {
            case 'METER':
                position = log_meter (value);
                meter.css({height: position + `%`});
                if (value >= 0) {
                    meter.css({boxShadow: `5px 5px 15px red`});                    
                } else if (value > -6) {
                    meter.css({boxShadow: `5px 5px 15px rgba(242, 121, 0, 0.8)`});
                } else {
                    meter.css({boxShadow: `5px 5px 15px rgba(35, 145, 0, 0.8)`});
                }
                break;
            case 'STATE':
                position = (Math.floor(value * 100)).toFixed();
                state.css({width: `${position}%`});
                state.text(`${position}%`);
                break;
            case 'ERRORS':
                if (value >= 3.0) {
                    popup.text(`Neural Record Error: Sample Rate mismatch, please use 48kHz`);
                    popup.css({display: 'block'});
                    setTimeout(function() { popup.css({display: 'none'}); }, 5000); 
                } else if (value >= 2.0) {
                    popup.text(`Neural Record Error: Seems we receive only garbage, we stop the process now`);
                    popup.css({display: 'block'});
                    setTimeout(function() { popup.css({display: 'none'}); }, 5000); 
                } else if (value >= 1.0) {
                    popup.text(`Neural Record Error: No signal comes in, we stop the process now`);
                    popup.css({display: 'block'});
                    setTimeout(function() { popup.css({display: 'none'}); }, 5000); 
                }
                break;
            default:
                break;
        }
    }

    if (event.type == 'start') {
        var ports = event.ports;
        for (var p in ports) {
            handle_event (ports[p].symbol, ports[p].value);
        }
    }
    else if (event.type == 'change') {
        handle_event (event.symbol, event.value);
    }
}
