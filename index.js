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

    const lCbutton = document.getElementById("listComparer")
    lCbutton.addEventListener("click", () => {
        window.location.href = "pages/listComparer.html"
    })

}

ready(main)