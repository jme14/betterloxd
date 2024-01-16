import {config} from "./tmdbConfig.js"

const TMDB_URL = config.api_base_url
const TMDB_KEY = config.api_key
const IMG_URL = config.image_base_url

export async function getFilmByTitleAndYear(title, year){

    title = title.replace(/ /g,'+')
    const searchString = `${TMDB_URL}search/movie?query=${title}&api_key=${TMDB_KEY}`
    const response = await fetch(searchString)
    const responseData = await response.json()

    const data = responseData?.results

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

export function getPosterPathFromTMDBData(tmdbData){
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