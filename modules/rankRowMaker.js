import { getFilmByTitleAndYear, getPosterPathFromTMDBData } from "./tmdbApi.js"

function supplyInfoButtonData(diaryTitle, diaryYear, divWithButtons) {
    let buttonArray = divWithButtons.querySelectorAll("button")

    for (let i = 0; i < buttonArray.length; i++) {
        const currentButton = buttonArray[i]
        currentButton.addEventListener("click", () => alertDiaryData(diaryTitle, diaryYear))
    }
}

function alertDiaryData(diaryTitle, diaryYear) {
    alert(`"${diaryTitle}", ${diaryYear}`)
}

function selectFilm(event, clone, pivotImageSrc) {
    console.log(event)
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
    containerDiv.className = "poster-container-container";

    // Create left poster container
    var leftPosterContainer = document.createElement("div");
    leftPosterContainer.className = "poster-container item";

    // Create left poster image container
    var leftPosterImgDiv = document.createElement("div");
    leftPosterImgDiv.className = "item poster-img leftFilmImgDiv";

    // Create left poster image
    var leftPosterImg = document.createElement("img");
    leftPosterImg.className = "leftFilmImg";
    leftPosterImg.id = `leftFilmImg-${number}`;
    leftPosterImg.src = pivotImgSrc;
    leftPosterImg.alt = "Placeholder poster";

    // Append left poster image to its container
    leftPosterImgDiv.appendChild(leftPosterImg);

    // Create left info button
    var leftInfoButton = document.createElement("button");
    leftInfoButton.className = "leftFilmInfoButton hiddenButton";
    leftInfoButton.id = `leftFilmInfoButton-${number}`;
    leftInfoButton.textContent = "More info";

    // Append left info button to its container
    leftPosterContainer.appendChild(leftPosterImgDiv);
    leftPosterContainer.appendChild(leftInfoButton);

    // Create right poster container
    var rightPosterContainer = document.createElement("div");
    rightPosterContainer.className = "poster-container item";

    // Create right poster image container
    var rightPosterImgDiv = document.createElement("div");
    rightPosterImgDiv.className = "item poster-img rightFilmImgDiv";

    // Create right poster image
    var rightPosterImg = document.createElement("img");
    rightPosterImg.className = "rightFilmImg";
    rightPosterImg.id = `rightFilmImg-${number}`;
    rightPosterImg.alt = "Placeholder poster";

    // Append right poster image to its container
    rightPosterImgDiv.appendChild(rightPosterImg);

    // Create right info button
    var rightInfoButton = document.createElement("button");
    rightInfoButton.className = "rightFilmInfoButton";
    rightInfoButton.id = `rightFilmInfoButton-${number}`;
    rightInfoButton.textContent = "More info";

    // Append right info button to its container
    rightPosterContainer.appendChild(rightPosterImgDiv);
    rightPosterContainer.appendChild(rightInfoButton);

    // Add event listeners to left and right side 
    leftPosterContainer.addEventListener("click", (event) => selectFilm(event, number, pivotImgSrc))
    rightPosterContainer.addEventListener("click", (event) => selectFilm(event, number, pivotImgSrc))

    // Append left and right poster containers to main container
    containerDiv.appendChild(leftPosterContainer);
    containerDiv.appendChild(rightPosterContainer);

    // Append main container to the body
    containerContainer.appendChild(containerDiv);

    tmdbData.then( (data) =>{

        rightPosterImg.src = getPosterPathFromTMDBData(data);
    })

}
