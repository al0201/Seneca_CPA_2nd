/**
 * WEB222 – Assignment 3
 *
 * I declare that this assignment is my own work in accordance with
 * Seneca Academic Policy. No part of this assignment has been
 * copied manually or electronically from any other source
 * (including web sites) or distributed to other students.
 *
 * Please update the following with your information:
 *
 *      Name:       Ahram Lee
 *      Student ID: alee239 / 133849232
 *      Date:       2024-07-15
 */

// All of our data is available on the global `window` object.
// Create local variables to work with it in this file.
const { artists, songs } = window;

// For debugging, display all of our data in the console. You can remove this later.
console.log({ artists, songs }, "Song and Artist App Data");

// DOM elements
const menu = document.getElementById("menu");
const selectedArtist = document.getElementById("selected-artist");
const songsTable = document.getElementById("songs");

// Create new funtion called 'createSongCard'
function createSongCard(song) {
  const card = document.createElement('div');
  card.classList.add("card");

  const songImg = document.createElement('img');
  songImg.src = song.imageUrl;
  songImg.classList.add("card-image");
  card.appendChild(songImg);

  const songTitle = document.createElement('h3');
  songTitle.textContent = song.title;
  card.appendChild(songTitle);

  const songYear = document.createElement('time');
  songYear.textContent = song.released;
  card.appendChild(songYear);

  const songDuration = document.createElement('span');
  songDuration.textContent = `${song.duration} sec`;
  card.appendChild(songDuration);

  const songLink = document.createElement('a');
  songLink.href = song.mediaUrl;
  songLink.textContent = "Listen";
  songLink.target = "_blank";
  card.appendChild(songLink);

  return card;
}

// Update the 'displaySongsByArtist' function to use 'loadSongs'
function loadSongs(artistId) {
  const container = document.getElementById('card-container');
  container.innerHTML = ''; // Clear existing cards

  const filteredSongs = songs.filter((song) => song.artistId === artistId);

  filteredSongs.forEach(song => {
    const card = createSongCard(song);
    container.appendChild(card);
  });
}

// Function to display songs by the selected artist
function displaySongsByArtist(artistId) {
  loadSongs(artistId);
}

// Function to create artist buttons
function createArtistButtons() {
  artists.forEach((artist) => {
    const button = document.createElement("button");
    button.textContent = artist.name;
    button.addEventListener("click", () => {
      displaySongsByArtist(artist.artistId);
      selectedArtist.textContent = artist.name;
    });
    menu.appendChild(button);
  });

  // Display the first artist's songs by default
  if (artists.length > 0) {
    displaySongsByArtist(artists[0].artistId);
    selectedArtist.textContent = artists[0].name;
  }
}

// Initialize the app
createArtistButtons();
