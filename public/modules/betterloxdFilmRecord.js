/* this class is used to more easily read how film data is being accessed */
export default class BetterloxdFilmRecord {
    constructor(rank, title, year, url, rating, watchedDate, description) {
        this.setRank(rank);
        this.setTitle(title);
        this.setYear(year);
        this.setUrl(url);
        this.setRating(rating);
        this.setWatchedDate(watchedDate);
        this.setDescription(description);
    }

    getRank() {
        return this.rank;
    }
    getTitle() {
        return this.title;
    }

    getYear() {
        return this.year;
    }

    getUrl() {
        return this.url;
    }

    getRating() {
        return this.rating;
    }

    getWatchedDate() {
        return this.watchedDate;
    }

    getDescription() {
        return this.description;
    }

    setRank(rank) {
        this.rank = rank;
    }
    setTitle(newTitle) {
        this.title = newTitle;
    }

    setYear(newYear) {
        this.year = newYear;
    }

    setUrl(newUrl) {
        this.url = newUrl;
    }

    setRating(newRating) {
        this.rating = newRating;
    }

    setWatchedDate(newWatchedDate) {
        this.watchedDate = newWatchedDate;
    }

    setDescription(newDescription) {
        this.description = newDescription;
    }

    /**
     * 
     * @param {BetterloxdFilmRecord} otherRecord the other instance of comparison 
     * @returns {boolean} true on equality, false otherwise 
     */
    equals(otherRecord) {
        return (
            this.getTitle() === otherRecord.getTitle()
            &&
            this.getYear() === otherRecord.getYear()
            &&
            this.getUrl() === otherRecord.getUrl()
        )
    }
}