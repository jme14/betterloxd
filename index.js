
function ready(fn){
    if ( document.readyState !== "loading" ){
        fn();
        return;
    }
    document.addEventListener("DOMContentLoaded", fn)
}


function main(){

    const hiderButton = document.getElementById("switcher")

    hiderButton.addEventListener("click", ()=> {
        const hiddenDiv = document.getElementById("hide-tester")
        const shownDiv = document.getElementById("show-tester")
        hiddenDiv.classList.remove("hidden-div")
        shownDiv.classList.add("hidden-div")

    })

}


ready(main)