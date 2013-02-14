collector = (typeof collector == "undefined") ? (function(){
    var interval;
    var time = 100;
    var collector = {};

    collector.start = function(){

        if(interval){
            return;
        }

        interval = setInterval(function(){
            var arr = window.stack;
            if(arr.length){
                window.stack = [];

                var result = 0;
                var sum = 0;

                var b = (+window.bottomline);
                for(var i=0;i<arr.length;i++){
                    var offset = (+arr[i]);

                    if(offset < window.bottomline){
                        // simultanious activity
                        result += b;
                    }else if( offset > topline){
                        // high activity, making wider
                        result += offset;
                    }else{
                        // no activity
                    } 

                    sum += offset;
                }

                HeadlessBrowser.genSnapshot(result);

            }
        }, time);
    }

    collector.stop = function(){
        if(interval){
            clearInterval(interval);
            interval = null;
        }
    }

    return collector;
})() : collector;
