import ready from './modules/ready.js';


function main(){

    const rFbutton = document.getElementById("ratingsFilter")
    rFbutton.addEventListener("click", () => {
        window.location.href = "pages/ratingRangeListMaker.html"
    })

    const yEbutton = document.getElementById("yearEndListMaker")
    yEbutton.addEventListener("click", () => {
        window.location.href = "pages/yearWatchedListMaker.html"
    })

  

    const lRbutton = document.getElementById("listRanker")
    lRbutton.addEventListener("click", ()=>{
        window.location.href = "pages/listRanker.html"
    })

}

ready(main)