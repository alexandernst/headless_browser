window.topline    = null;
window.bottomline = null;
window.stack      = [];

timer = (typeof timer == "undefined") ? (function(){

    var timer = {};

    var timeout = null;
    var started = false;

    timer.busy = function(){
        return started; 
    }

    timer.stop = function(){
        if(timeout){
            clearTimeout(timeout);
            timeout = false;
        }

        started = false;
    }

    timer.callibrate = function(callback){
        timer.collect(1, function(){
            var arr = stack;
            var map = {};

            for(var i=0;i < arr.length;i++){
               var c = arr[i]; 
                if(map[c]){
                    map[c]++;
                }else{
                    map[c] = 1; 
                }
            }

            var u = arr.length / 100;
            var maxline, minline, above = [], all   = [];

            for(var i in map){
                var c = map[i];
                var per = c / u;
                all.push([per, i]);
            }

            all.sort(function(a,b){
                var one = a[0];
                var two = b[0];
                if(one > two){
                    return -1;
                }else if(one < two){
                    return 1;
                }
                return 0;
            });

            var one = all[0];
            var two = all[1];

            above = all.length ? [ one[1], all.length == 1 ? one[1] : two[1] ] : [];
            above.sort();

            minline = above[0];
            maxline = above[1];
            
            if(maxline!=null && minline!=null){
                topline = maxline;
                bottomline = minline;
                callback && callback();
            }
        });
    }

    timer.collect = function(sec, callback){
        if(started){
            return;
        }

        started = true;
        var counter = 0;

        if(sec){
            // limited version
            var sum = sec * 1000;
            var nr = ~~(sum / (topline ? topline : 1));

            // allocating approx number of items in array
            // to avoid loading the CPU with dynamic array
            stack = new Array(nr);

            var i = 0;
            (function(){

                var scope = arguments.callee;
                var s = (+new Date());
                
                timeout = setTimeout(function(){
                    var e = (+new Date());
                    var offset = e-s;

                    counter += offset;

                    stack[i++] = (offset);

                    if(counter < sum){
                        scope();
                    }else{
                        timer.stop();
                        // cleaning the rest
                        while(stack.length){
                            if(stack[stack.length-1] != null){
                                break;
                            }
                            stack.pop();
                        }

                        if(callback){
                            callback();
                        }
                    }
                },0);
            })();
        }else{
            stack = [];
            (function scope(){
                var s = (+new Date());
                if(started){
                    timeout = setTimeout(function(info){
                        var e = (+new Date());
                        var offset = e - s;
                        stack.push(offset);
                        scope();
                    }, 0);
                }
            })();
        }
        return stack;
    }

    return timer;
})() : timer;
