var index = 0;
var audioElements = document.getElementsByTagName('audio');
console.log('Audio elements gathered')

function playNext(index) {
    audioElements[index].play();
    $(audioElements[index]).bind("ended", function(){
        index++;
        if(index < audioElements.length){
            console.log('Playing last')
            playNext(index);        
        }
    });
}

$(document).ready(function() {
    $("#play").click(function() {
        console.log('Start play')
        audioElements[index].play();
        $(audioElements[index]).bind("ended", function(){
             index = index + 1;
             if(index < audioElements.length){
                console.log('Playing next')
                playNext(index); 

             }                        
        });
    });
});
