import { getFilmByTitleAndYear, getPosterPathFromTMDBData } from "./tmdbApi.js"


function displayFilmInformation(filmRecord){
    alert(`${filmRecord.getTitle()} (${filmRecord.getYear()})`)
}

/** 
* @param {HTMLElement} event 
* @param {number} number 
* @param {string} pivotImageSrc 
*/
function selectFilm(chosenFilm){

    let filmsParent = chosenFilm.parentNode.parentNode.parentNode
    filmsParent.classList.remove("unselected")

    let notChosenFilm = getUnchosenFromParentDiv(filmsParent, chosenFilm)
    markFirstSelected(chosenFilm, notChosenFilm)


    function getUnchosenFromParentDiv(parentDiv, chosenFilm){
        let notChosenFilm = parentDiv.children[1].children[0].children[0];
        if ( notChosenFilm === chosenFilm ) {
            notChosenFilm = parentDiv.children[0].children[0].children[0]
        } 

        return notChosenFilm 
    }
    function markFirstSelected(chosenFilm, notChosenFilm){
        chosenFilm = chosenFilm.parentNode
        notChosenFilm = notChosenFilm.parentNode

        if (chosenFilm.classList.contains("chosenFilm")) return;
        if (chosenFilm.classList.contains("notChosenFilm")) {
            chosenFilm.classList.remove("notChosenFilm")
            notChosenFilm.classList.remove("chosenFilm")
        }

        chosenFilm.classList.add("chosenFilm")
        notChosenFilm.classList.add("notChosenFilm")

    }
}

/** 
* Creates a row entry for each film record called 
* @param containerContainer {HTMLElement} container containing all the rows 
* @param filmRecord {BetterloxdFilmRecord} film record as defiend in betterloxdFilmRecord.js
* @param number {int} the nth row, used for giving elements ids 
* @param pivotImgSrc {String} the src string to the poster of the filmRecord 
*/
export default function addRow(containerContainer, pivotImgSrc, filmRecord, number){
    let tmdbData = getFilmByTitleAndYear(filmRecord.getTitle(), filmRecord.getYear())

    // Create container div
    var containerDiv = document.createElement("div");
    containerDiv.id = `container-${number}`;
    containerDiv.className = "poster-container-container unselected";

    // Create left poster container
    var leftPosterContainer = document.createElement("div");
    leftPosterContainer.className = "poster-container item";

    // Create left poster image container
    var leftPosterImgDiv = document.createElement("div");
    leftPosterImgDiv.className = "item poster-img leftFilmImgDiv";
    leftPosterImgDiv.id = `leftFilmImgDiv-${number}`

    // Create left poster image
    var leftPosterImg = document.createElement("img");
    leftPosterImg.className = "leftFilmImg";
    leftPosterImg.id = `leftFilmImg-${number}`;
    leftPosterImg.src = pivotImgSrc;
    leftPosterImg.alt = "Placeholder poster";

    // Append left poster image to its container
    leftPosterImgDiv.appendChild(leftPosterImg);

    // Append left info button to its container
    leftPosterContainer.appendChild(leftPosterImgDiv);

    // Create right poster container
    var rightPosterContainer = document.createElement("div");
    rightPosterContainer.className = "poster-container item";

    // Create right poster image container
    var rightPosterImgDiv = document.createElement("div");
    rightPosterImgDiv.className = "item poster-img rightFilmImgDiv";
    rightPosterImgDiv.id = `rightFilmImgDiv-${number}`

    // Create right poster image
    var rightPosterImg = document.createElement("img");
    rightPosterImg.className = "rightFilmImg";
    rightPosterImg.id = `rightFilmImg-${number}`;
    rightPosterImg.alt = "Placeholder poster";

    // Append right poster image to its container
    rightPosterImgDiv.appendChild(rightPosterImg);

    // Add event listeners to left and right side 
    leftPosterImg.addEventListener("click", (event) => selectFilm(event.target))
    rightPosterImg.addEventListener("click", (event) => selectFilm(event.target))

    // Create right info button
    var rightInfoButton = document.createElement("button");
    rightInfoButton.className = "rightFilmInfoButton";
    rightInfoButton.id = `rightFilmInfoButton-${number}`;
    rightInfoButton.textContent = "More info";


    //Add event listener to right info button 
    rightInfoButton.addEventListener("click", () => displayFilmInformation(filmRecord))

    // Append right info button to its container
    rightPosterContainer.appendChild(rightPosterImgDiv);
    rightPosterContainer.appendChild(rightInfoButton);

    // Append left and right poster containers to main container
    containerDiv.appendChild(leftPosterContainer);
    containerDiv.appendChild(rightPosterContainer);

    // Append main container to the body
    containerContainer.appendChild(containerDiv);

    tmdbData.then( (data) =>{

        rightPosterImg.src = getPosterPathFromTMDBData(data);
    })

}
