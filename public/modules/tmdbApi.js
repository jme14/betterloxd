



export async function getFilmByTitleAndYear(title, year, tmdbData){

    const TMDB_URL = tmdbData.TMDB_URL
    const TMDB_KEY = tmdbData.TMDB_KEY

    title = title.replace(/ /g,'+')
    const searchString = `${TMDB_URL}search/movie?query=${title}&api_key=${TMDB_KEY}`
    const response = await fetch(searchString)
    if ( response.status === 404){
        console.log(searchString)
        throw new Error("Search string not found")
    }
    const responseData = await response.json()

    const data = responseData?.results
    if ( data === null) {
        alert("Can't look up films right now, try again later")
        return null;
    }

    for ( let i = 0 ; i < data.length ; i++){
        const yearFromData = data[i].release_date.split("-")[0]
        if (yearFromData === year.toString()){
            return data[i]
        }
    }

    for ( let i = 0 ; i < data.length ; i++){
        const yearFromData = data[i].release_date.split("-")[0]
        if (Math.abs(yearFromData - year.toString()) < 2){
            return data[i]
        }
    }

    console.log(`WARNING: RELEASE YEAR NOT EVEN CLOSE TO RIGHT FOR ${title}`)
    return data[0]
}

export function getPosterPathFromTMDBData(IMG_URL,tmdbData){
    let posterPath = null 
    try{
        posterPath = tmdbData.posterPath
        const imgPath = `${IMG_URL}${tmdbData.poster_path}`
        return imgPath
    } catch(error) {
        console.log(error)
        console.log(tmdbData)
        return ""
    }

}